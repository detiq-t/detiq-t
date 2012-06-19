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

#include "ImageWindow.h"

using namespace genericinterface;
using namespace imagein;

ImageWindow::ImageWindow(QString path): _path(path)
{
    _sourceWindow =  NULL;
    _applicationArea = new Rectangle();
    _statusBar = new QStatusBar();
}

ImageWindow::ImageWindow(QString path, const ImageWindow* source, Rectangle* rect): QWidget(), _sourceWindow(source), _path(path)
{
    if(rect)
        _applicationArea = new Rectangle(*rect);
    else
        _applicationArea = new Rectangle();

    _statusBar = new QStatusBar();
}

void ImageWindow::activated()
{
    emit(highlightRectChange(_applicationArea, this));
}

void ImageWindow::setApplicationArea(const imagein::Rectangle* rect)
{
    _applicationArea->x = rect->x;
    _applicationArea->y = rect->y;
    _applicationArea->w = rect->w;
    _applicationArea->h = rect->h;
}

QString ImageWindow::getTitleFromPath(QString path)
{
    std::string p = path.toStdString();
    size_t pos = p.rfind("\\");

    if(pos != std::string::npos)
        p = p.substr(pos + 1);
    else if((pos = p.rfind("/")) != std::string::npos)
        p = p.substr(pos + 1);

    return QString::fromStdString(p);
}

