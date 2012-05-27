//#include "ComponentLabeling.h"

#include "Otsu.h"

#include <algorithm>
#include <cmath>

namespace imagein {
	namespace algorithm {

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
			D foreground = (_blackBackground) ? std::numeric_limits<D>::max() : 0; 
			
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
					std::vector<unsigned int> neighbours;

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
				for(unsigned int i = 1 ; i < img->getWidth() ; ++i) {
					if(img->getPixel(i, j) == foreground) {
						std::vector<unsigned int> neighbours;
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
			unsigned int colourNo = 0;
			for(unsigned int j = 0 ; j < img->getHeight() ; ++j) {
				for(unsigned int i = 0 ; i < img->getWidth() ; ++i) {
					if(img->getPixel(i, j) == foreground) {
						unsigned int name = _synonyms.find(labels[i + j*img->getWidth()]);
						labels[i + j*img->getWidth()] = name;
						if(_nameToColour.count(name) == 0) {
							_nameToColour.insert(std::pair<unsigned int, unsigned int>(name, colourNo++));
							_nameToSize.insert(std::pair<unsigned int, unsigned int>(name, 0));
						}
						
						_nameToSize[name]++;
					}
						
				}
			}
			
			D** colours;
			if(getNbComponents() > 0) {
				//Color table construction
				colours = new D*[getNbComponents()];
				double step = 360 / static_cast<double>(getNbComponents());
				for(unsigned int i = 0 ; i < getNbComponents() ; ++i) {
					colours[i] = new D[3];
					
					double hue = static_cast<double>(i) * step / 60.0; //sector for hue
					
					double mod;
					double decimal = std::modf(hue, &mod);
					unsigned short int x = 255 * (1 - std::abs((static_cast<double>(static_cast<unsigned int>(mod)%2) + decimal) - 1));
					
					if(hue < 1) {
						colours[i][0] = 255;
						colours[i][1] = x;
						colours[i][2] = 0;
					}
					else if(hue < 2) {
						colours[i][0] = x;
						colours[i][1] = 255;
						colours[i][2] = 0;
					}
					else if(hue < 3) {
						colours[i][0] = 0;
						colours[i][1] = 255;
						colours[i][2] = x;
					}
					else if(hue < 4) {
						colours[i][0] = 0;
						colours[i][1] = x;
						colours[i][2] = 255;
					}
					else if(hue < 5) {
						colours[i][0] = x;
						colours[i][1] = 0;
						colours[i][2] = 255;
					}
					else {
						colours[i][0] = 255;
						colours[i][1] = 0;
						colours[i][2] = x;
					}
				}
			}
			
			int step = (getNbComponents() / 3) - 1;
			
			D* data = new D[img->getWidth() * img->getHeight() * 3];
			for(unsigned int j = 0 ; j < img->getHeight() ; ++j) {
				for(unsigned int i = 0 ; i < img->getWidth() ; ++i) {
					if(img->getPixel(i, j) == foreground) {
						data[3*i + 3*j*img->getWidth()] = colours[((_nameToColour.find(labels[i + j*img->getWidth()])->second) * step)%getNbComponents()][0];
						data[3*i + 3*j*img->getWidth() + 1] = colours[((_nameToColour.find(labels[i + j*img->getWidth()])->second) * step)%getNbComponents()][1];
						data[3*i + 3*j*img->getWidth() + 2] = colours[((_nameToColour.find(labels[i + j*img->getWidth()])->second) * step)%getNbComponents()][2];
					}
					else {
						data[3*i + 3*j*img->getWidth()] = img->getPixel(i,j);
						data[3*i + 3*j*img->getWidth() + 1] = img->getPixel(i,j);
						data[3*i + 3*j*img->getWidth() + 2] = img->getPixel(i,j);
					}
				}
			}
			
			for(unsigned int i = 0 ; i < getNbComponents() ; ++i) {
				delete[] colours[i];
			}
			delete[] colours;
			
			return new RgbImage_t<D>(img->getWidth(), img->getHeight(), data);
		}

		template <typename D>
		double ComponentLabeling_t<D>::getAverageComponentSize() const
		{
			double average = 0;
			for(std::map<unsigned int, unsigned int>::const_iterator it = _nameToSize.begin() ; it != _nameToSize.end() ; ++it) {
				average += static_cast<double>(it->second);
			}
			return average/static_cast<double>(_nameToSize.size());
		}

		//DisjointSet Implementation
		//----------------------------

		template<typename D>
		void ComponentLabeling_t<D>::DisjointSet::makeSet()
		{
			unsigned int n = _tab.size();
			_tab.push_back(new std::list<unsigned int>(1, n));
		}

		template<typename D> 
		void ComponentLabeling_t<D>::DisjointSet::merge(unsigned int s1, unsigned int s2)
		{
			if(_tab[s2] != _tab[s1]) {
				_tab[s1]->splice(_tab[s1]->end(), *(_tab[s2]));
				delete _tab[s2];
				
				std::list<unsigned int>* toReplace = _tab[s2];
				for(std::vector<std::list<unsigned int> *>::iterator it = _tab.begin() ; it != _tab.end() ; ++it) {
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
				
				std::list<unsigned int>* cur = _tab[i];
				
				if(i == e) return i; //If we're searching for a set representative, we know it's in that set
				
				if(std::find(cur->begin(), cur->end(), e) != cur->end()) {
					return i;
				}
			}
		}
	}
}
