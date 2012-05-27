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
  void initTestCase();
  void testWindowServiceAddFile();
  void testFileServiceSave();
  void testShowHistogram();
  void cleanupTestCase();

private:
  GenericInterface _gi;
  StandardImageWindow* _img;
};

void TestGenericInterface::initTestCase() {
  _gi.run();
}

void TestGenericInterface::testWindowServiceAddFile() {

  WindowService* ws = dynamic_cast<WindowService*>(_gi.getService(GenericInterface::WINDOW_SERVICE));

  ws->addFile(QString("test.jpg"));
  _img = dynamic_cast<StandardImageWindow*>(ws->getCurrentImageWindow());

  QVERIFY((void*)_img != (void*)0);

  QCOMPARE(QString("test.jpg"), ws->getCurrentImageWindow()->getPath());
}

void TestGenericInterface::testFileServiceSave() {

  FileService* fs = dynamic_cast<FileService*>(_gi.getService(GenericInterface::FILE_SERVICE));
  fs->save("tata.jpg");

  Image test("test.jpg"), tata("tata.jpg");

  QCOMPARE(test.getWidth(),      tata.getWidth());
  QCOMPARE(test.getHeight(),     tata.getHeight());
  QCOMPARE(test.getNbChannels(), tata.getNbChannels());
}

void TestGenericInterface::testShowHistogram() {
  _img->showHistogram();

  WindowService* ws = dynamic_cast<WindowService*>(_gi.getService(GenericInterface::WINDOW_SERVICE));

  HistogramWindow* hw;
  hw = dynamic_cast<HistogramWindow*>(ws->getCurrentImageWindow());
  const Histogram* h = dynamic_cast<HistogramView*>(hw->getView())->getHistogram(0);

  QVERIFY((void*)hw != (void*)0);

  const Image* img = _img->getImage();
  Histogram h2 = img->getHistogram();

  QCOMPARE(h->getWidth(), h2.getWidth());

  for(int i = 0; i < h->getWidth(); i++)
    QCOMPARE((*h)[i], h2[i]);
}

void TestGenericInterface::cleanupTestCase() {
  QFile("tata.jpg").remove();
}

QTEST_MAIN(TestGenericInterface)
#include "Tests.moc"








/*
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
*/

