TEMPLATE = app
LIBS += -lqwt -limagein -lpng -ljpeg -lGenericInterface
TARGET = 
DEPENDPATH += . Widgets
INCLUDEPATH += . Widgets

# Input
HEADERS += FilteringService.h Widgets/FilterChoice.h Widgets/FilterEdition.h
SOURCES += FilteringService.cpp \
           main.cpp \
           Widgets/FilterChoice.cpp \
           Widgets/FilterEdition.cpp
