#ifndef DITHERINGSERVICE_H
#define DITHERINGSERVICE_H

#include <Services/AlgorithmService.h>

#include <QToolBar>

/*!
* \brief First implementation of AlgorithmService with basic algorithms
*
* It contains the algorithm Identity and Inversion
*/
class DitheringService : public genericinterface::AlgorithmService
{
	Q_OBJECT
	public:
		void display(genericinterface::GenericInterface* gi);
		void connect(genericinterface::GenericInterface* gi);

	public slots:
		void applyDithering();

	private:
		QAction* _dithering;
};

#endif
