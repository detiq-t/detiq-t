#include <QtTest/QtTest>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <GenericInterface.h>
#include <Widgets/ImageWidgets/StandardImageWindow.h>
#include <Widgets/ImageWidgets/StandardImageView.h>

using namespace imagein;
using namespace genericinterface;

class TestGenericInterface : public QObject
{
  Q_OBJECT
private slots:
  void testImageWindow();
  
};

void TestGenericInterface::testImageWindow() {
  GenericInterface gi;
  gi.run();

  WindowService* ws = dynamic_cast<WindowService*>(gi.getService(GenericInterface::WINDOW_SERVICE));

  ws->addFile(QString("test.jpg"));
  StandardImageWindow* imgw;
  imgw = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());
  QGraphicsView* v;
  v = dynamic_cast<StandardImageView*>(imgw->getStandardView())->getGraphicsView();
  QTest::mouseMove(v, QPoint(100, 10));
  QTest::mouseClick(v, Qt::LeftButton, 0, QPoint(100, 10));
  QTest::mousePress(v->viewport(), Qt::LeftButton, 0, QPoint(100, 10));
  QTest::qWait(500);
  QTest::mouseMove(v, QPoint(150, 20));
  QTest::qWait(500);
  QTest::mouseRelease(v->viewport(), Qt::LeftButton, 0, QPoint(150, 20));

  QTest::qWait(10000);

  const Rectangle* rect = imgw->getSelection();

  QCOMPARE(rect->x, static_cast<unsigned int>(10));
  QCOMPARE(rect->y, static_cast<unsigned int>(10));
}

QTEST_MAIN(TestGenericInterface)
#include "Tests.moc"
