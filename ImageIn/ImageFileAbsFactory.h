#ifndef IMAGEFILEABSFACTORY_H
#define IMAGEFILEABSFACTORY_H

#include "ImageFileFactory.h"

namespace imagein {

    /*!
     * \brief Class used to retrieve or change the ImageFileFactory
     *
     * To add a new format to ImageIn, follow these steps :
     * -# Create a class deriving from ImageFile and reimplement the methods defined in it.
     * -# Create a class deriving from ImageFileFactory and reimplement the method getImageFile() so that it can return your ImageFile class when it needs to
     * (don't forget to call the original getImageFileMethod so you dont remove Jpg, Png and Bmp support).
     * -# call the method ImageFileAbsFactory::setFactory(), passing an instance of your newly created factory class.
     *
     * The file format will then be available to use within the Image classes.
     *
     * \sa ImageFileFactory::getImageFile()
     */
    class ImageFileAbsFactory
    {
        public:
            //! Retrieves the factory set by the user, or the default factory.
            static const ImageFileFactory* getFactory()
            {
                return ImageFileAbsFactory::_factory;
            }

            //! Sets a new factory for use in Image class.
            static void setFactory(ImageFileFactory* factory)
            {
                delete ImageFileAbsFactory::_factory;
                ImageFileAbsFactory::_factory = factory;
            }

        private:
            static ImageFileFactory* _factory;
    };
}


#endif // IMAGEFILEABSFACTORY_H
