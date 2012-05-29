#ifndef BINARIZATIONSERVICE_H
#define BINARIZATIONSERVICE_H

#include <Services/AlgorithmService.h>
#include "BinarizationWidget.h"

#include <QToolBar>

using namespace genericinterface;

/*!
 * \brief Service that offers the possibility to Binarize an Image.
 *
 * It allow to use the Otsu's algorithm or to choose one or two manual thresholds.
 */
class BinarizationService : public AlgorithmService
{
    Q_OBJECT
public:
    void display(GenericInterface* gi);
    void connect(GenericInterface* gi);

private slots:
    /**
     * \brief Open the widget to binarize the current Image.
     *
     * It will first check if the Image is a grayscale, if not it will display a message.
     */
    void applyBinarization();

    /**
     * \brief Extract the binarized image of the widget.
     *
     * \param path The path of the source image.
     * \param im The image from the widget.
     */
    void exportBinarizedImage(QString& path, Image* im);

    void aboutOtsu();

private:
    QAction* _binarize;
    BinarizationWidget* _binWidget;
};

#endif
