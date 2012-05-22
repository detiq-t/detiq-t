#ifndef MORPHOMATSERVICE_H
#define MORPHOMATSERVICE_H

#include <Algorithm/MorphoMat.h>

#include <Services/AlgorithmService.h>

#include <QToolBar>

namespace genericinterface
{
    class MorphoMatService : public AlgorithmService
    {
      Q_OBJECT
      public:
        MorphoMatService(); 
        void display(GenericInterface* gi);
        void connect(GenericInterface* gi);
        imagein::MorphoMat::StructElem<depth_default_t>* getStructElem() { return _structElem; }
        void setStructElem(imagein::MorphoMat::StructElem<depth_default_t>* structElem) { _structElem = structElem; }

      public slots:
	    void editStructElem();
        void applyErosion();
	    void applyDilatation();
	    void applyGradient();

      private:
        QToolBar* _toolBar;
        imagein::MorphoMat::StructElem<depth_default_t>* _structElem; 
        QAction* _editStructElem;
	    QAction* _erosion;
	    QAction* _dilatation;
	    QAction* _gradient;
    };
}

#endif
