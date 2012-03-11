#ifndef ALGORITHMCOLLECTION_H
#define ALGORITHMCOLLECTION_H

#include <vector>

#include "Image.h"
#include "GenericAlgorithm.h"
#include "Algorithm.h"
#include "AlgorithmException.h"

namespace imagein
{
	template <typename Depth>
	class AlgorithmCollection {
		public:

			void Add(const GenericAlgorithm_t<Depth>& algo) {
				_algorithms.push_back(algo);
			}

			Image_t<Depth>* operator()(const std::vector<Image_t<Depth>*>& images) {
				if(_algorithms.size()==0) throw EmptyAlgorithmCollectionException(__LINE__, __FILE__);
				Image_t<Depth>* lastImage = *(_algorithms.begin())(images);
				for(typename std::vector<const GenericAlgorithm_t<Depth>& >::iterator it = _algorithms.begin()+1; it < _algorithms.end(); ++it) {
					lastImage = (*it)(lastImage);
				}
				return lastImage;
			}

			inline Image_t<Depth>* operator() (const Image_t<Depth>* img) { std::vector<const Image_t<Depth>*> imgs; imgs.push_back(img); (*this)(imgs); }

		private:
			std::vector<const GenericAlgorithm_t<Depth>& > _algorithms;
	};
}

#endif //!ALGORITHMCOLLECTION_H