###################################################################################
#                                                                                 #
# QT PROJECT FOR BUILDING EMULIB LIBRARY FOR WIN32 and LINUX                      #
#                                                                                 #
#                                                                                 #
###################################################################################
include("../config.pri")




###################################################################################
# LIST ALL PROJECT DEPENDENCIES HERE
# "SOURCES" and "HEADERS" ARE USED BY QT FOR THE BUILD
# APPROPRIATE FILES ARE ADDED TO THESE BELOW THIS SECTION
###################################################################################

LIB_SOURCES += \
	 ../baselib_source/0.Framework/*.cpp	\
	 ../baselib_source/1.DataTypes/*.cpp	\
	 #LIB_SOURCES

LIB_HEADERS += \
	 ../baselib_source/0.Framework/*.h		\
	 ../baselib_source/1.DataTypes/*.h		\
	#LIB_HEADERS

SOURCES += $$LIB_SOURCES
HEADERS += $$LIB_HEADERS





###################################################################################
#                                                                                 #
#                          Compilation settings                                   #
#                                                                                 #
###################################################################################
# Set the type of project
QT -= gui
CONFIG -= app_bundle
TEMPLATE = lib



##################################################################################
#                                                                                #
#                          QMake settings														#
#                                                                                #
##################################################################################

# Statically link compiler libraries for release builds
CONFIG(debug,debug|release):QMAKE_LFLAGS += -static
CONFIG(release,debug|release):QMAKE_LFLAGS += -static

# Specify -fPIC if building a shared library (debug mode)
CONFIG(debug,debug|release):QMAKE_LFLAGS += -fPIC
CONFIG(debug,debug|release):CONFIG += -fPIC





##################################################################################
#                                                                                #
#                          Target Files														#
#                                                                                #
##################################################################################
# Set Target
# In windows, .dll is added automatically in dynamically linked builds
win32:CONFIG(debug,debug|release):TARGET = baselib_win32d
# In windows, lib is prefixed and .a is added automatically in statically linked builds
win32:CONFIG(release,debug|release):TARGET = baselib_win32

# In linux, lib is prefixed and .so is added automatically in dynamically linked builds
unix:CONFIG(debug,debug|release):TARGET = baselib_linuxd
# In linux, lib is prefixed and .a is added automatcially in statically linked builds
unix:CONFIG(release,debug|release):TARGET = baselib_linux









