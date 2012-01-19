#############################################################################
# Makefile for building: ImageIn
#
# Do not forget to add dependency rules whenever you add an #include in a file.
# Do not forget to add a target whenever you add a new cpp file.
#
# See the FUS courses from last year for info on writing a Makefile !
#
#############################################################################

####### Compiler, tools and options

CC            = g++ #Compiler
LINK          = g++ #Linker
DEFINES       =     #Compiler defines
CXXFLAGS      = -g -Wall $(DEFINES) #Compiler options. Do not forget to append the defines
LIBS          = -lpng -ljpeg -lz # Libs to link with the library

####### Output directory

OBJECTS_DIR   = debug

####### Files

SOURCES       = BinaryImage.cpp \
		BmpImage.cpp \
		ImageFileFactory.cpp \
		ImageFileAbsFactory.cpp \
		JpgImage.cpp \
		main.cpp \
		PngImage.cpp \
		ProjectionHistogram.cpp
OBJECTS       = debug/BinaryImage.o \
		debug/BmpImage.o \
		debug/ImageFileFactory.o \
		debug/ImageFileAbsFactory.o \
		debug/JpgImage.o \
		debug/main.o \
		debug/PngImage.o \
		debug/ProjectionHistogram.o
DESTDIR        = debug/ #avoid trailing-slash linebreak
TARGET         = ImageIn.exe
DESTDIR_TARGET = debug/ImageIn.exe

####### Implicit rules

.SUFFIXES: .cpp .cc .cxx .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

####### Build rules

$(DESTDIR_TARGET):  $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(DESTDIR_TARGET) $(OBJECTS)  $(LIBS)

clean:
	rm -f $(OBJECTS) $(DESTDIR_TARGET)

####### Compile

debug/BinaryImage.o: BinaryImage.cpp BinaryImage.h \
		GrayscaleImage.h \
		Image.h \
		Rectangle.h \
		Histogram.h \
		Array.h \
		Image.tpp \
		GrayscaleImage.tpp \
		Histogram.tpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/BinaryImage.o BinaryImage.cpp

debug/BmpImage.o: BmpImage.cpp BmpImage.h \
		ImageFile.h \
		ImageFileException.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/BmpImage.o BmpImage.cpp

debug/ImageFileFactory.o: ImageFileFactory.cpp ImageFileFactory.h \
		ImageFile.h \
		ImageFileException.h \
		JpgImage.h \
		PngImage.h \
		BmpImage.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/ImageFileFactory.o ImageFileFactory.cpp

debug/ImageFileAbsFactory.o: ImageFileAbsFactory.cpp ImageFileAbsFactory.h \
		ImageFileFactory.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/ImageFileAbsFactory.o ImageFileAbsFactory.cpp
	

debug/JpgImage.o: JpgImage.cpp JpgImage.h \
		ImageFile.h \
		ImageFileException.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/JpgImage.o JpgImage.cpp

debug/main.o: main.cpp Image.h \
		Rectangle.h \
		Histogram.h \
		Array.h \
		Image.tpp \
		BinaryImage.h \
		GrayscaleImage.h \
		GrayscaleImage.tpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/main.o main.cpp

debug/PngImage.o: PngImage.cpp PngImage.h \
		ImageFile.h \
		ImageFileException.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/PngImage.o PngImage.cpp

debug/ProjectionHistogram.o: ProjectionHistogram.cpp ProjectionHistogram.h \
		Array.h \
		Image.h \
		Rectangle.h \
		Histogram.h \
		Image.tpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o debug/ProjectionHistogram.o ProjectionHistogram.cpp

