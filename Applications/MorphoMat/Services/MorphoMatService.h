#ifndef MORPHOMATSERVICE_H
#define MORPHOMATSERVICE_H

#include <Algorithm/MorphoMat.h>

#include <Services/AlgorithmService.h>
#include "../Widgets/StructElemWindow.h"

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
	    void applyOpening();
	    void applyClosing();
	    void applyWhiteTopHat();
	    void applyBlackTopHat();
        void checkActionsValid(QMdiSubWindow* activeWindow);

      private:
        imagein::MorphoMat::StructElem<depth_default_t>* _structElem; 
        QAction* _editStructElem;
	    QAction* _erosion;
	    QAction* _dilatation;
	    QAction* _erosion2;
	    QAction* _dilatation2;
	    QAction* _opening;
	    QAction* _closing;
	    QAction* _gradient;
	    QAction* _wtophat;
	    QAction* _btophat;
        void applyOperator(MorphoMat::Operator<depth_default_t>& op);
        StructElemWindow* _structElemWindow;
    };
}

#endif
