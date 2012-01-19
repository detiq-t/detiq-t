#ifndef IMAGEFILEABSFACTORY_H
#define IMAGEFILEABSFACTORY_H

#include "ImageFileFactory.h"

namespace imagein {

    class ImageFileAbsFactory
    {
        public:
            static const ImageFileFactory* getFactory()
            {
                return _factory;
            }

            static void setFactory(ImageFileFactory* factory)
            {
                delete _factory;
                _factory = factory;
            }

        private:
            static ImageFileFactory* _factory;
    };

    ImageFileFactory* ImageFileAbsFactory::_factory = new ImageFileFactory();
}


#endif // IMAGEFILEABSFACTORY_H
