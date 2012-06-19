/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

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

