#include "FilterEdition.h"

#include <QLineEdit>

using namespace filtrme;

FilterEdition::FilterEdition(int width, int height, const QString & name, QList<QWidget> args) : _width(width), _height(height)
{
  _name = new QLineEdit(name);

  _editionZone = new QVBoxLayout;
}

QString FilterEdition::name() const
{
  return _name->text();
}
