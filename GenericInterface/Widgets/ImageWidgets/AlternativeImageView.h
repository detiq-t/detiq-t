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

#ifndef ALTERNATIVEIMAGEVIEW_H
#define ALTERNATIVEIMAGEVIEW_H

#include <QWidget>

#include <Image.h>
using namespace imagein;

namespace genericinterface
{
	/*!
     * \brief Inherited class by all Views except StandardImageView
     *
     * The AlternativeImageView class contain the Image and inherits QWidget.
     */
    class AlternativeImageView : public QWidget
    {
    protected:
        const Image* _image;
        
    public:
		/*!
		* \brief Default constructor.
		* 
		* Constructs an empty QWidget.
		* The image must be initialized for every view.
		*
		* \param image The view entry-level image
		*/
		AlternativeImageView(const Image* image);
		
		//! Returns the image
		inline const Image* getImage() const { return _image; }
    };
}

#endif // ALTERNATIVEIMAGEVIEW_H
