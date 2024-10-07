QT += core testlib

# List all source files
SOURCES +=

    ./EmailGenerator/functions.cpp
    ./EmailGenerator/main.cpp
    ./testfiledata.cpp
    ./testgenerateemail.cpp
    ./testwriteoutput.cpp

# Include the source files from the main project
SOURCES += ../emailGeneratorProgram/functions.cpp
HEADERS += ../emailGeneratorProgram/functions.h

INCLUDEPATH += ../emailGeneratorProgram

SUBDIRS += \
    EmailGenerator/emailGeneratorProgram.pro

QMAKE_CXXFLAGS += -v
QMAKE_CFLAGS += -v
