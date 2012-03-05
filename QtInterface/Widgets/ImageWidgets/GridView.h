#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include "GraphicsView.h"
#include "AlternativeImageView.h"

#include <Image.h>
using namespace imagein;

namespace genericinterface
{
    class GridView : public AlternativeImageView
    {
		Q_OBJECT
	private:
		GraphicsView* _view;
        
	public:
		GridView(Image* image);
		GraphicsView* getGraphicsView();
		
	public slots:
        //void ctrlPressed();
        
	signals:
		void pixelClickedLeft(int x, int y);
		void pixelClickedRight(int x, int y);
		void pixelHovered(int x, int y);
    };
}

#endif // GRIDVIEW_H
