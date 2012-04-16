#ifndef FILTERINGSERVICE_H
#define FILTERINGSERVICE_H

#include <Services/AlgorithmService.h>

#include "../../ImageIn/Algorithm/Filtering.h"
#include "Widgets/FilterChoice.h"

#include <QStringList>

namespace genericinterface
{
  /*!
   * \brief Implementation of AlgorithmService for Filtering application
	*
	* It allows to apply filter on image
	*/
  class FilteringService : public AlgorithmService
  {
  Q_OBJECT
  public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

  public slots:
    void applyFiltering();
    void apply(imagein::algorithm::Filtering*);

  private:
    FilterChoice* _filterChoice;
    QAction* _filtering;
    QStringList _texts;
  };
}

#endif //FILTERINGSERVICE_H
