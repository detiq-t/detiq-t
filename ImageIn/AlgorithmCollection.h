#ifndef ALGORITHMCOLLECTION_H
#define ALGORITHMCOLLECTION_H

#include <vector>

#include "Image.h"
#include "GenericAlgorithm.h"
#include "Algorithm.h"
#include "AlgorithmException.h"

namespace imagein
{
    template <typename Depth, unsigned int A>
    class AlgorithmCollection {
        public:

            AlgorithmCollection(const GenericAlgorithm_t<Depth, A>& algo) : _topAlgorithm(algo) {
            }

            void Add(const GenericAlgorithm_t<Depth, 1>& algo) {
                _nestedAlgorithms.push_back(algo);
            }

            Image_t<Depth>* operator()(const std::vector<Image_t<Depth>*>& images) {
                //if(_algorithms.size()==0) throw EmptyAlgorithmCollectionException(__LINE__, __FILE__);
                Image_t<Depth>* lastImage = _topAlgorithm(images);
                for(typename std::vector<GenericAlgorithm_t<Depth> >::iterator it = _nestedAlgorithms.begin()+1; it < _nestedAlgorithms.end(); ++it) {
                    lastImage = (*it)(lastImage);
                }
                return lastImage;
            }

            inline Image_t<Depth>* operator() (const Image_t<Depth>* img) { std::vector<const Image_t<Depth>*> imgs; imgs.push_back(img); (*this)(imgs); }

        private:
            std::vector<GenericAlgorithm_t<Depth, 1> > _nestedAlgorithms;
            GenericAlgorithm_t<Depth, 1> _topAlgorithm;
    };
}

#endif //!ALGORITHMCOLLECTION_H
