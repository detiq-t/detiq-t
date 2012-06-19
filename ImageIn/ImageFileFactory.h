/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef IMAGEFILEFACTORY_H
#define IMAGEFILEFACTORY_H

#include <string>

#include "ImageFile.h"


namespace imagein
{
    /*!
     * \brief This is the factory used to get the right ImageFile instance based on the filename of the image.
     *
     * To add a new format to ImageIn, follow these steps :
     * -# Create a class deriving from ImageFile and reimplement the methods defined in it.
     * -# Create a class deriving from ImageFileFactory and reimplement the method getImageFile(std::string filename) so that it can return your ImageFile class when it needs to
     * (don't forget to call the original getImageFileMethod so you dont remove Jpg, Png and Bmp support).
     * -# call the method ImageFileAbsFactory::setFactory(ImageFileFactory*), passing an instance of your newly created factory class.
     *
     * The file format will then be available to use within the Image classes.
     *
     * \sa ImageFileFactory::getImageFile(sdt::string), ImageFileAbsFactory::setFactory(ImageFileFactory*)
     */
    class ImageFileFactory
    {
        public:

            /*!
             * \brief Returns the depth of the given image.
             *
             * Uses the polymorphic method getImageFile(std::string), so this method can handle any file type that your factory can.
             *
             * \param filename The image file you want the info on.
             */
            unsigned int getImageDepth(std::string filename) const;

            /*!
             * \brief Returns the right ImageFile object for your file.
             *
             * This method will choose the right ImageFile object based on the filename you passed.
             * For performance reason, the content of the file is not checked before you actually try to read from it.
             *
             * This is the method you need to redefine in sub-classes if you want to add support for another file format.
             * You will then need to pass an instance of your own factory to ImageFileAbsFactory::setFactory(ImageFileFactory*) so it is used by Image class.
             *
             * \param filename The image file you want to perform operations on.
             * \sa ImageFileAbsFactory, Image::Image()
             */
            virtual ImageFile* getImageFile(std::string filename) const;
    };
}

#endif // IMAGEFILEFACTORY_H
