#ifndef BASICTOOLS_H
#define BASICTOOLS_H

#include <Services/AlgorithmService.h>

#include <QMenu>

using namespace genericinterface;

/*!
* \brief A service that offers some basics tools
*/
class BasicTools : public AlgorithmService
{
    Q_OBJECT
public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

public slots:
    void applyIdentity();
    void applyInversion();
    void convertToGrayscale(); // call an algorithm to transform to a grayscale image

private:
    QMenu* _menu;
    QAction* _identity;
    QAction* _inversion;
    QAction* _convertToGrayscale;
};

#endif
