#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QString>
#include <iostream>
#include <sstream>

#include <Rectangle.h>

#include "AlternativeImageView.h"

namespace genericinterface
{
/*!
   * \brief Inherited class by all Windows
   *
   * The ImageWindow class contains the status bar and inherit QWidget.
   */
class ImageWindow : public QWidget
{
        Q_OBJECT
    protected:
        imagein::Rectangle* _applicationArea;
        QStatusBar* _statusBar;
        const ImageWindow* _sourceWindow;
        QString _path;

    public:
        ImageWindow(QString path);
        /*!
         * \brief Default constructor.
         *
         * Constructs an empty QWidget and initialized the source window and the application area from parameters.
         *
         * \param source The source window
         * \param rect The application area (Rectangle used for Histogram, Algorithm...)
         */
        ImageWindow(QString path, const ImageWindow *source, Rectangle *rect = 0);

        /*!
         * \brief Returns the title from a path.
         *
         * \param path The path of a file.
         */
        static QString getTitleFromPath(QString path);

        QString getPath(){ return _path; }

        QString getName(){ return getTitleFromPath(_path); }

        /*!
         * \brief Returns the view in the window.
         *
         */
        virtual AlternativeImageView* getView()=0;

    public slots:
        void activated();
        void setApplicationArea(const imagein::Rectangle* rect);

    signals:
        /*!
         * \brief Signal emits when this is activated
         *
         * \param rect Rectangle to display on the source window
         */
        void highlightRectChange(const imagein::Rectangle* rect, ImageWindow* source);
    };
}

#endif // IMAGEWINDOW_H
