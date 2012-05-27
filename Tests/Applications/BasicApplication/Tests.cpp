#include <QtTest/QtTest>
#include <QObject>
#include <Algorithm/Identity.h>
#include <Algorithm/Inversion.h>
#include <cmath>

#include <GenericInterface.h>
#include "../../Applications/BasicApplication/BasicAlgorithmService.h"

using namespace imagein;
using namespace genericinterface;

class TestBasicApplication : public QObject
{
  Q_OBJECT
private slots:
  void initTestCase();
  void testIdentityApplication();
  void testInversionApplication();
  void cleanupTestCase();

private:
  GenericInterface _gi;
  BasicAlgorithmService _bas;
  int _id;
};

void TestBasicApplication::initTestCase() {
  _id = _gi.addService(&_bas);
  _gi.run();
}

void TestBasicApplication::testIdentityApplication() {
  WindowService* ws = dynamic_cast<WindowService*>(_gi.getService(GenericInterface::WINDOW_SERVICE));

  ws->addFile(QString("grayscale.jpg"));
  _bas.applyIdentity();

  FileService* fs = dynamic_cast<FileService*>(_gi.getService(GenericInterface::FILE_SERVICE));
  fs->save("identityByAppli.jpg");

  Image t("grayscale.jpg");

  /* construire l'algo */
  algorithm::Identity<Image> algo;
  Image* hand = algo(&t);
  Image* appli = new Image("identityByAppli.jpg");

  for(unsigned int i = 0; i < hand->getHeight(); i++)
    for(unsigned int j = 0; j < hand->getWidth(); j++)
      for(unsigned int nb = 0; nb < hand->getNbChannels(); nb++) {
        QVERIFY(std::abs(hand->getPixel(j, i, nb) - appli->getPixel(j, i, nb)) < 3);
      }

  delete appli;
  delete hand;
}

void TestBasicApplication::testInversionApplication() {
  WindowService* ws = dynamic_cast<WindowService*>(_gi.getService(GenericInterface::WINDOW_SERVICE));

  ws->addFile(QString("grayscale.jpg"));
  _bas.applyInversion();

  FileService* fs = dynamic_cast<FileService*>(_gi.getService(GenericInterface::FILE_SERVICE));
  fs->save("identityByAppli.jpg");

  Image t("grayscale.jpg");

  /* construire l'algo */
  algorithm::Inversion<Image> algo;
  Image* hand = algo(&t);
  Image* appli = new Image("identityByAppli.jpg");

  for(unsigned int i = 0; i < hand->getHeight(); i++)
    for(unsigned int j = 0; j < hand->getWidth(); j++)
      for(unsigned int nb = 0; nb < hand->getNbChannels(); nb++) {
        QVERIFY(std::abs(hand->getPixel(j, i, nb) - appli->getPixel(j, i, nb)) < 3);
      }

  delete appli;
  delete hand;
}

void TestBasicApplication::cleanupTestCase() {
  QFile("identityByAppli.jpg").remove();
}

QTEST_MAIN(TestBasicApplication)
#include "Tests.moc"

