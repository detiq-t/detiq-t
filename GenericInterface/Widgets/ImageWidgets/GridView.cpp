#include <QHBoxLayout>
#include <QGraphicsView>
#include <vector>

#include "GridView.h"
#include "ImageViewer.h"
#include "ZoomViewer.h"

using namespace imagein;
using namespace genericinterface;

ChannelSelector::ChannelSelector(const QString& name, int nb)
  : QRadioButton(name), _nb(nb)
{
  if(nb == 0)
    setChecked(true);
  QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(send(bool)));
}

void ChannelSelector::send(bool b)
{
  if(b)
    emit activated(_nb);
}

RadioPanel::RadioPanel(int nb)
{
  std::vector<QString> names;

  names.resize(nb);

  if(nb == 3)
  {
    names[0] = "R";
    names[1] = "G";
    names[2] = "B";
  }

  QHBoxLayout* l = new QHBoxLayout();

  for(int i = 0; i < nb; i++)
  {
    ChannelSelector* b = new ChannelSelector(names[i], i);
    QObject::connect(b, SIGNAL(activated(int)), this, SLOT(rcvActivated(int)));
    l->addWidget(b);
  }

  setLayout(l);
}

void RadioPanel::rcvActivated(int a)
{
  emit activated(a);
}

GridView::GridView(Image* im, const QString & path, int dx, int dy)
  : AlternativeImageView(im)
{
    _layout = new QHBoxLayout;
    _viewer = new ImageViewer(path, dx, dy);

    QVBoxLayout *layout = new QVBoxLayout();

    QGraphicsView* view = new QGraphicsView;
    view->setScene(_viewer);

    RadioPanel* panel = new RadioPanel(im->getNbChannels());

    layout->addWidget(view);
    layout->addWidget(panel);
    _layout->addLayout(layout);

    ZoomViewer* zv = new ZoomViewer(im, ImageViewer::RECT_W, ImageViewer::RECT_H);
    QGraphicsView* viewz = new QGraphicsView;
    viewz->setScene(zv);
    _layout->addWidget(viewz);

    QObject::connect(panel, SIGNAL(activated(int)), zv, SLOT(channelChosen(int)));

    QObject::connect(_viewer, SIGNAL(positionUpdated(int, int)), zv, SLOT(draw(int, int)));

    setLayout(_layout);
}
