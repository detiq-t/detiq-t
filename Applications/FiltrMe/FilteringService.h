#ifndef FILTERINGSERVICE_H
#define FILTERINGSERVICE_H

#include <Services/AlgorithmService.h>

#include "Widgets/FilterChoice.h"

#include <QStringList>
#include <pthread.h>

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
    
    void applyAlgorithm(imagein::algorithm::Filtering* algo);

  public slots:
    void applyFiltering();
    void apply(imagein::algorithm::Filtering*);

  private:
   /* #ifdef __linux__
    static void* parallelAlgorithm(void* data);
    #endif*/
  
    FilterChoice* _filterChoice;
    QAction* _filtering;
    QStringList _texts;
			
    /*#ifdef __linux__
    struct ThreadArgs
    {
      imagein::algorithm::Filtering* filtering;
      GenericInterface* gi;
    };
    #endif*/
  };
}

#endif //FILTERINGSERVICE_H
