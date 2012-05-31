TEMPLATE = app
LIBS += -lqwt -limagein -lpng -ljpeg -lGenericInterface
QT += xml
TARGET = 
DEPENDPATH += . Widgets
INCLUDEPATH += . Widgets

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
