TEMPLATE = app
LIBS += -lqwt -limagein -lpng -ljpeg -lGenericInterface
QT += xml
TARGET = 
DEPENDPATH += . Widgets
INCLUDEPATH += . Widgets ../../GenericInterface ../../ImageIn
LIBS += -L../../GenericInterface -lGenericInterface -L../../ImageIn -limagein -lpng -ljpeg
CONFIG += qwt

# Input
HEADERS += FilteringService.h \
           Widgets/FilterChoice.h \
           Widgets/FilterEditor.h \
           Widgets/FilterEditorItem.h
SOURCES += FilteringService.cpp \
           main.cpp \
           Widgets/FilterChoice.cpp \
           Widgets/FilterEditor.cpp \
           Widgets/FilterEditorItem.cpp
