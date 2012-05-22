#ifndef ALGO_COMPONENTLABELING_H
#define ALGO_COMPONENTLABELING_H

#include "../Image.h"
#include "../GrayscaleImage.h"
#include "../Algorithm.h"
#include "../RgbImage.h"

#include <vector>
#include <list>
#include <map>

namespace imagein 
{
    namespace algorithm
    {
        /*!
         * \brief Connected component labeling.
         * 
		 * This algorithm aims to identify the connected component of the image. Each connected component will be 
         * given a different colour. This works only on binary images. The behavior of this algorithm is undefined 
         * for non-binary images, but you can binarize it before the application using the constructor's third parameter.
         *
         * Explanation of the algorithm : http://en.wikipedia.org/wiki/Connected-component_labeling
         *
         * Arity : 1 \n
         * Input type :  GrayscaleImage_t<D> \n
         * Output type : RgbImage_t<D> \n
         * Complexity : O(n*m) with n and m being the width and height of the image.
         *
         * \tparam D the depth of the input and output image
         */
        template <typename D>
        class ComponentLabeling_t : public Algorithm_t<RgbImage_t<D>, 1>
        {
            public:
				//! Connectivity to use for the objects.
				typedef enum {CONNECT_8, CONNECT_4} Connectivity;
				
                /*!
                 * \brief Default constructor. Allows to specify the parameters of the algorithm.
                 *
                 * \param connect The connectivity of the algorithm. CONNECT_8 means that the 8 neighbours of a pixel will be used for
                 * the algorithm. CONNECT_4 means that only the North, West, South and East neighbours will be used. Default is CONNECT_8
                 * \param blackBackground If true, The black pixels will be used for background, and white pixel for the objects (foreground). Default is false.
                 * \param binarizeInput If true, the input image will be binarized using the Otsu_t algorithm. Behaviour is undefined if your input is not a 
                 * Binary Image.
                 */
                ComponentLabeling_t(Connectivity connect = CONNECT_8, bool blackBackground = false, bool binarizeInput = false) 
				 : _connect(connect), _blackBackground(blackBackground), _binarizeInput(binarizeInput) {};
			 
                //! Returns the number of components found in the image.
				unsigned int getNbComponents() const { return _nameToColour.size(); };

                //!Returns the average size of the components.
				double getAverageComponentSize() const;

            protected:

                /*! Implementation of the algorithm.
                 * 
                 * see the documentation of GenericAlgorithm_t, SpecificAlgorithm_t and Algorithm_t for
                 * informations on the Algorithm interface.
                 */
                RgbImage_t<D>* algorithm(const std::vector<const Image_t<D>*>& imgs);
            
            private:
				
				Connectivity _connect;
				bool _blackBackground;
				bool _binarizeInput;
				std::map<unsigned int, unsigned int> _nameToColour;
				std::map<unsigned int, unsigned int> _nameToSize;
				
				class DisjointSet
				{
					public:
						
						//Insert a new subset with its representative
						void makeSet();
						
						//Merge two sets
						void merge(unsigned int s1, unsigned int s2);
						
						//Finds in which subset an element is. If it is in several subset, the first is returned.
						unsigned int find(unsigned int e) const;
						
						//Clears the table.
						void clear() { _tab.clear(); }
						
					private:
						std::vector<std::list<unsigned int>* > _tab;
				};
				
				DisjointSet _synonyms;
        };

        typedef ComponentLabeling_t<depth_default_t> ComponentLabeling; //!< Standard Algorithm with default depth. See Image_t::depth_default_t
    }
}
#include "ComponentLabeling.tpp"

#endif
