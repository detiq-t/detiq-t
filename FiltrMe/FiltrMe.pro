TEMPLATE = app
LIBS += -lqwt -limagein -lpng -ljpeg -lQtInterface
TARGET = 
DEPENDPATH += . Widgets
INCLUDEPATH += . Widgets

# Input
HEADERS += Widgets/FilterEdition.h
SOURCES += main.cpp Widgets/FilterEdition.cpp
