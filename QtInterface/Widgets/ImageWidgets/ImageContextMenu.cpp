#include "ImageContextMenu.h"

using namespace genericinterface;

ImageContextMenu::ImageContextMenu(QWidget* parent): QMenu(parent){}

void ImageContextMenu::showContextMenu(const QPoint& pos)
{
	this->popup(parentWidget()->mapToGlobal(pos));
}
