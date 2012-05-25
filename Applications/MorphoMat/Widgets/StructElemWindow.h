#ifndef STRUCTELEMWINDOW_H 
#define STRUCTELEMWINDOW_H

#include <Algorithm/MorphoMat.h>
#include <Algorithm/Binarization.h>
#include <Algorithm/Otsu.h>
#include <Converter.h>

#include <Widgets/ImageWidgets/StandardImageWindow.h>
#include <Widgets/ImageWidgets/HistogramWindow.h>
#include <Widgets/ImageWidgets/GridView.h>

#include "StructElemViewer.h"

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QToolBar>
#include <QMdiSubWindow>
#include <QFormLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QPushButton>

class StructElemWindow : public QMdiSubWindow
{
    Q_OBJECT
  public:
    StructElemWindow(imagein::MorphoMat::StructElem<depth_default_t>*& elemi, QAction* button);
    void changeStructElem(imagein::MorphoMat::StructElem<depth_default_t>* elem);

  public slots:
    void openFile();
    void saveFile();
    void ok();
    void resize(int size);
    void generate();

  protected:
    void closeEvent ( QCloseEvent * event );

  private:
    QWidget* _widget;
    QToolBar* _toolBar;
    QAction* _openFile;
    QAction* _ok;
    QAction* _saveFile;
    genericinterface::HistogramWindow* _histo;
    QLabel* _labelThreshold;
    imagein::MorphoMat::StructElem<depth_default_t>* _structElem;
    imagein::MorphoMat::StructElem<depth_default_t>*& _serviceStructElem;
    QGraphicsView* _view;
    StructElemViewer *_viewer;
    imagein::GrayscaleImage_t<bool> _realSize;
    QAction* _tbButton;
    QPushButton* _genButton; 
    QComboBox* _shapeToGen;
    QSpinBox* _shapeSize;

};

#endif
