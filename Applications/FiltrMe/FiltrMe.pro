TEMPLATE = app
LIBS += -lqwt -limagein -lpng -ljpeg -lGenericInterface
TARGET = 
DEPENDPATH += . Widgets
INCLUDEPATH += . Widgets
QT += xml

# Input
HEADERS += FilteringService.h Widgets/FilterChoice.h Widgets/FilterEditor.h
SOURCES += FilteringService.cpp \
           main.cpp \
           Widgets/FilterChoice.cpp \
           Widgets/FilterEditor.cpp
