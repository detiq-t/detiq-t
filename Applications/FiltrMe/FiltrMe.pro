TEMPLATE = app
LIBS += -lqwt -limagein -lpng -ljpeg -lGenericInterface
TARGET = 
DEPENDPATH += . Widgets
INCLUDEPATH += . Widgets

# Input
HEADERS += FilteringService.h \
           Widgets/FilterChoice.h \
           Widgets/FilterEdition.h \
           ../../ImageIn/Algorithm/Filtering.h \
           ../../ImageIn/Image.h \
           ../../ImageIn/mystdint.h \
           ../../ImageIn/pstdint.h \
           ../../ImageIn/Rectangle.h \
           ../../ImageIn/Histogram.h \
           ../../ImageIn/Array.h \
           ../../ImageIn/Histogram.tpp \
           ../../ImageIn/Image.tpp \
           ../../ImageIn/ImageFile.h \
           ../../ImageIn/ImageFileException.h \
           ../../ImageIn/ImageFileAbsFactory.h \
           ../../ImageIn/ImageFileFactory.h \
           ../../ImageIn/Algorithm.h \
           ../../ImageIn/SpecificAlgorithm.h \
           ../../ImageIn/GenericAlgorithm.h \
           ../../ImageIn/AlgorithmException.h \
           ../../ImageIn/GenericAlgorithm.tpp \
           ../../ImageIn/SpecificAlgorithm.tpp \
           ../../ImageIn/Algorithm.tpp \
           ../../ImageIn/Algorithm/Filter.h \
           ../../ImageIn/Algorithm/Filtering.tpp \
           ../../ImageIn/Algorithm/Average.h \
           ../../ImageIn/PixelAlgorithm.h \
           ../../ImageIn/Converter.h \
           ../../ImageIn/GrayscaleImage.h \
           ../../ImageIn/GrayscaleImage.tpp \
           ../../ImageIn/BadImageException.h \
           ../../ImageIn/RgbImage.h \
           ../../ImageIn/RgbImage.tpp \
           ../../ImageIn/Converter.tpp \
           ../../ImageIn/Algorithm/Distance.h
SOURCES += FilteringService.cpp \
           main.cpp \
           Widgets/FilterChoice.cpp \
           Widgets/FilterEdition.cpp \
           ../../ImageIn/ImageFileAbsFactory.cpp \
           ../../ImageIn/ImageFileFactory.cpp \
           ../../ImageIn/Algorithm/Filter.cpp
