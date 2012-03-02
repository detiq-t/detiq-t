#ifndef ALTERNATIVEIMAGEVIEW_H
#define ALTERNATIVEIMAGEVIEW_H

#include <QWidget>

#include <Image.h>
using namespace imagein;

namespace genericinterface
{
    class AlternativeImageView : public QWidget
    {
    protected:
        Image* _image;
    public:
		AlternativeImageView();
		AlternativeImageView(Image* image);
    };
}

#endif // ALTERNATIVEIMAGEVIEW_H
