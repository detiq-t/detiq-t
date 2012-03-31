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
