//#include "ComponentLabeling.h"

#include "Otsu.h"

#include <algorithm>

using namespace imagein;
using namespace imagein::algorithm;
using namespace std;

template <typename D>
RgbImage_t<D>* ComponentLabeling_t<D>::algorithm(const std::vector<const Image_t<D>*>& imgs)
{
	_nameToColour.clear();
	_nameToSize.clear();
	_synonyms.clear();
	
	const GrayscaleImage_t<D>* img = dynamic_cast<const GrayscaleImage_t<D>*>(imgs.at(0));
    if(img == NULL) {
        throw ImageTypeException(__LINE__, __FILE__);
    }
	
	//Binarize input image if needed
	if(_binarizeInput) {
		Otsu_t<D> o;
		img = o(img);
	}
	
	//foreground color
	D foreground = (_blackBackground) ? numeric_limits<D>::max() : 0; 
	
	//Create label matrix.
	unsigned int* labels = new unsigned int[img->getWidth() * img->getHeight()];
	
	//First pass.
	unsigned int curLabel = 0;
	
	if(img->getPixel(0, 0) == foreground) { //first cell
		labels[0] = curLabel++;
		_synonyms.makeSet();
	}
	else {
		labels[0] = -1;
	}	
	
	for(unsigned int i = 1 ; i < img->getWidth() ; ++i) { //first line
		if(img->getPixel(i, 0) == foreground) {
			if(img->getPixel(i-1, 0) == foreground) {
				labels[i] = labels[i-1];
			}
			else {
				labels[i] = curLabel++;
				_synonyms.makeSet();
			}
		}
		else {
			labels[i] = -1;
		}
	}
	
	for(unsigned int j = 1 ; j < img->getHeight() ; ++j) {
		
		//first cell
		if(img->getPixel(0, j) == foreground) {
			vector<unsigned int> neighbours;

			if(_connect == CONNECT_8 && img->getPixel(1, j-1) == foreground) {
				neighbours.push_back(labels[1+(j-1)*img->getWidth()]);
			}
			if(img->getPixel(0, j-1) == foreground) {
				neighbours.push_back(labels[(j-1)*img->getWidth()]);
			}
			
			if(neighbours.size() == 0) {
				labels[j*img->getWidth()] = curLabel++;
				_synonyms.makeSet();
			}
			else {
				std::sort(neighbours.begin(), neighbours.end());
				labels[j*img->getWidth()] = neighbours[0];
				for(unsigned int k = 1 ; k < neighbours.size() ; ++k) {
					_synonyms.merge(neighbours.at(0), neighbours.at(k));
				}
			}
		}
		else {
			labels[j*img->getWidth()] = -1;
		}
		
		//rest of the line
		for(int i = 1 ; i < img->getWidth() ; ++i) {
			if(img->getPixel(i, j) == foreground) {
				vector<unsigned int> neighbours;
				if(_connect == CONNECT_8) {
					if(img->getPixel(i-1, j-1) == foreground) {
						neighbours.push_back(labels[i-1+(j-1)*img->getWidth()]);
					}
					
					try { //we may be on the last cell...
						if(img->getPixel(i+1, j-1) == foreground) {
							neighbours.push_back(labels[i+1+(j-1)*img->getWidth()]);
						}
					}
					catch(std::out_of_range) {}
				}
				if(img->getPixel(i, j-1) == foreground) {
					neighbours.push_back(labels[i+(j-1)*img->getWidth()]);
				}
				if(img->getPixel(i-1, j) == foreground) {
					neighbours.push_back(labels[i-1+j*img->getWidth()]);
				}
				
				if(neighbours.size() == 0) {
					labels[i + j*img->getWidth()] = curLabel++;
					_synonyms.makeSet();
				}
				else {
					std::sort(neighbours.begin(), neighbours.end());
					labels[i + j*img->getWidth()] = neighbours.at(0);
					for(unsigned int k = 1 ; k < neighbours.size() ; ++k) {
						if(neighbours.at(0) != neighbours.at(k)) {
							_synonyms.merge(neighbours.at(0), neighbours.at(k));
						}
					}
				}
			}
			else {
				labels[i + j*img->getWidth()] = -1;
			}
		}
	}
	//end first pass. Each pixel has a label, synonyms table is full.
	
	//second pass
	D* data = new D[img->getWidth() * img->getHeight() * 3];
	unsigned int colourNo = 0;
	for(unsigned int j = 0 ; j < img->getHeight() ; ++j) {
		for(unsigned int i = 0 ; i < img->getWidth() ; ++i) {
			if(img->getPixel(i, j) == foreground) {
				unsigned int name = _synonyms.find(labels[i + j*img->getWidth()]);
				labels[i + j*img->getWidth()] = name;
				if(_nameToColour.count(name) == 0) {
					_nameToColour.insert(pair<unsigned int, unsigned int>(name, colourNo++));
					_nameToSize.insert(pair<unsigned int, unsigned int>(name, 0));
				}
				
				_nameToSize[name]++;
				
				data[3*i + 3*j*img->getWidth()] = colours[(_nameToColour.find(name)->second)%nColours][0];
				data[3*i + 3*j*img->getWidth() + 1] = colours[(_nameToColour.find(name)->second)%nColours][1];
				data[3*i + 3*j*img->getWidth() + 2] = colours[(_nameToColour.find(name)->second)%nColours][2];
			}
			else {
				data[3*i + 3*j*img->getWidth()] = img->getPixel(i,j);
				data[3*i + 3*j*img->getWidth() + 1] = img->getPixel(i,j);
				data[3*i + 3*j*img->getWidth() + 2] = img->getPixel(i,j);
			}
		}
	}
	
	//TEMPORARY : prints the labels.
	// for(unsigned int j = 0 ; j < img->getHeight() ; ++j) {
		// for(unsigned int i = 0 ; i < img->getWidth() ; ++i) {
			// if(labels[i + j * img->getWidth()] == (unsigned)-1) cout << -1 << "\t";
			// else cout << labels[i + j * img->getWidth()] << "\t";
		// }
		// cout << endl;
	// }
	
	return new RgbImage_t<D>(img->getWidth(), img->getHeight(), data);
}

template <typename D>
double ComponentLabeling_t<D>::getAverageComponentSize() const
{
	double average = 0;
	for(map<unsigned int, unsigned int>::const_iterator it = _nameToSize.begin() ; it != _nameToSize.end() ; ++it) {
		average += static_cast<double>(it->second);
	}
	return average/static_cast<double>(_nameToSize.size());
}

template <typename D>
D ComponentLabeling_t<D>::colours[nColours][3] = {  
	{numeric_limits<D>::max(),0,0}, 
	{0,numeric_limits<D>::max(),0}, 
	{0,0,numeric_limits<D>::max()},
	{numeric_limits<D>::max(),numeric_limits<D>::max(),0}, 
	{0,numeric_limits<D>::max(),numeric_limits<D>::max()}, 
	{numeric_limits<D>::max(),0,numeric_limits<D>::max()}, 
	{numeric_limits<D>::max()/2,numeric_limits<D>::max()/2,numeric_limits<D>::max()/2} 
};

//DisjointSet Implementation
//----------------------------

template<typename D>
void ComponentLabeling_t<D>::DisjointSet::makeSet()
{
	unsigned int n = _tab.size();
	_tab.push_back(new list<unsigned int>(1, n));
}

template<typename D> 
void ComponentLabeling_t<D>::DisjointSet::merge(unsigned int s1, unsigned int s2)
{
	if(_tab[s2] != _tab[s1]) {
		_tab[s1]->splice(_tab[s1]->end(), *(_tab[s2]));
		delete _tab[s2];
		
		list<unsigned int>* toReplace = _tab[s2];
		for(vector<list<unsigned int> *>::iterator it = _tab.begin() ; it != _tab.end() ; ++it) {
			if(*it == toReplace) {
				*it = _tab[s1];
			}
		}
		
	}
}

template<typename D> 
unsigned int ComponentLabeling_t<D>::DisjointSet::find(unsigned int e) const
{
	for(unsigned int i = 0 ; i < _tab.size() ; ++i) {
		
		list<unsigned int>* cur = _tab[i];
		
		if(i == e) return i; //If we're searching for a set representative, we know it's in that set
		
		if(std::find(cur->begin(), cur->end(), e) != cur->end()) {
			return i;
		}
	}
}