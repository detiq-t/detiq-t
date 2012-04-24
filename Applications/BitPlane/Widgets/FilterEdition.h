#ifndef WIDGET_FILTEREDITION
#define WIDGET_FILTEREDITION

#include <QWidget>
#include <QVBoxLayout>
#include <QString>
#include <QList>

class QLineEdit;

namespace filtrme
{
  class FilterEdition : public QWidget
  {
  public:
    FilterEdition(int width, int height, const QString & name = "", QList<QWidget> args = QList<QWidget>());

    /**
    * @brief Get the name of the edited filter
    *
    * @return A QString object of the text
    */
    QString name() const;
  protected:
    QVBoxLayout*  _editionZone; /*!< the layout of this widget */
  private:
    void displayArguments();

    QLineEdit*    _name;        /*!< the text edit fir the name of the filter */
    int           _width;
    int           _height;
  };
}

#endif
