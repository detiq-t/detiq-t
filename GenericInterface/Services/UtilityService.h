#ifndef QTINTERFACE_UTILITYSERVICE_H
#define QTINTERFACE_UTILITYSERVICE_H

#include "../GenericInterface.h"

#include <QMenu>

namespace genericinterface
{
	class UtilityService : public QObject, public Service
	{
		Q_OBJECT
		public:
			void display(GenericInterface* gi);
			void connect(GenericInterface* gi);


		public slots:
			
			//These are the slots for actions on StandardImageWindow
			void showHistogram();
			void showHProjectionHistogram();
			void showVProjectionHistogram();
			void showPixelsGrid();
			
			void checkActionsValid(QMdiSubWindow* activeWindow);
		signals:

		private:
			GenericInterface* _gi;
			QMenu* _showMenu;
			
			QAction* _showHistogram;
			QAction* _showHProjectionHistogram;
			QAction* _showVProjectionHistogram;
			QAction* _showPixelsGrid;
	};
}

#endif
