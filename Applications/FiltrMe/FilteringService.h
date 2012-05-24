#ifndef FILTERINGSERVICE_H
#define FILTERINGSERVICE_H

#include <Services/AlgorithmService.h>

#include "Widgets/FilterChoice.h"
#include "Widgets/FilterEditor.h"

#include <QStringList>
#include <pthread.h>

namespace filtrme
{
  /*!
   * \brief Implementation of AlgorithmService for Filtering application
	*
	* It allows to apply filter on image
	*/
  class FilteringService : public genericinterface::AlgorithmService
  {
  Q_OBJECT
  public:
    void display(genericinterface::GenericInterface* gi);
    void connect(genericinterface::GenericInterface* gi);
    
    void applyAlgorithm(imagein::algorithm::Filtering* algo);

  public slots:
    void applyFiltering();
    void edition();
    void apply(imagein::algorithm::Filtering*);
    void cancelAction();

  private:  
    FilterChoice* _filterChoice;
    FilterEditor* _filterEditor;
    QAction* _filtering;
    QAction* _filterEdition;
    QStringList _texts;
  };
}

#endif //FILTERINGSERVICE_H
