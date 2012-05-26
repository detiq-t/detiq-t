#ifndef QTINTERFACE_FILESERVICE_H
#define QTINTERFACE_FILESERVICE_H

#include <QMessageBox>
#include <QFileDialog>

#include "../GenericInterface.h"
#include "WindowService.h"

namespace genericinterface
{
	class FileService : public QObject, public Service
	{
		Q_OBJECT
		public:
			void connect (GenericInterface* gi);
			void display (GenericInterface* gi);

		public slots:
			void save(const QString& path = QString(), const QString& ext = QString());
			void saveAs();
	        void checkActionsValid(QMdiSubWindow* activeWindow);
		
		private slots:
			void chooseFile();

		signals:
			void fileChosen(const QString& path);

		private:
			QAction* _open;
			QAction* _save;
			QAction* _saveAs;

			GenericInterface* _gi;
	};
}

#endif
