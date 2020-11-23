QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = soldering

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix:HOME = $$system(echo $HOME)
win32:HOME = $$system(echo %userprofile%)

CONFIG(debug, debug|release){
BUILD = debug
} else {
BUILD = release
}

COMMON_LIBS = commonlib

equals(BUILD,debug) {
    #message( "build is _ debug" )
    COMMON_LIBS = $$COMMON_LIBS"_debug"
}

equals(BUILD,release){
    COMMON_LIBS = $$COMMON_LIBS"_release"
}

equals(QT_ARCH, x86_64){
    COMMON_LIBS = $$COMMON_LIBS"_64"
}

equals(QT_ARCH, x86){
    COMMON_LIBS = $$COMMON_LIBS"_32"
}

equals(QT_ARCH, arm){
    COMMON_LIBS = $$COMMON_LIBS"_arm"
}

message( "architecture = "$$QT_ARCH )
message( "commonlibs folder = "$$COMMON_LIBS )

#unix:HOME = $$system(echo $HOME)
#win32:HOME = $$system(echo %userprofile%)

# INSTALLDIR = $$COMMON_LIBS
COMMON_LIBS_FULLPATH = $$shell_path($$HOME/$$COMMON_LIBS)

message( " commonlibs full path = "$$COMMON_LIBS_FULLPATH)

#unix:!macx: LIBS += -L/home/zoli/build-common-Desktop_Qt_5_12_2_GCC_64bit2-Debug/stringhelper/ -lstringhelper
unix:!macx:
{
message( "hmmmm "$$HOME/$$COMMON_LIBS)
LIBS += -L$$COMMON_LIBS_FULLPATH/ -llogger
#LIBS += -L$$COMMON_LIBS_FULLPATH/ -lsignalhelper
#LIBS += -L$$COMMON_LIBS_FULLPATH/ -lCommandLineParserHelper
#LIBS += -L$$COMMON_LIBS_FULLPATH/ -lcoreappworker
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lstringhelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -ltextfilehelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lfilehelper
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lmacrofactory
LIBS += -L$$COMMON_LIBS_FULLPATH/ -lshortguid
#LIBS += -L$$COMMON_LIBS_FULLPATH/ -linihelper
#LIBS += -L$$COMMON_LIBS_FULLPATH/ -lsettingshelper
#LIBS += -L$$COMMON_LIBS_FULLPATH/ -lxmlhelper
}

INCLUDEPATH += $$HOME/common
DEPENDPATH += $$HOME/common

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    utilityPi_soldering_hu_HU.ts

#LIBS += -L/home/anti/raspi/sysroot/usr/lib -lraspicam -lraspicam_cv
#LIBS += -L/home/anti/raspi/sysroot/usr/lib/lib -lopencv_dnn -lopencv_gapi -lopencv_highgui -lopencv_ml -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_video -lopencv_videoio -lopencv_imgcodecs -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_imgproc -lopencv_core
LIBS += -L/home/anti/raspi/sysroot/usr/lib/arm-linux-gnueabihf
LIBS += -L/home/anti/raspi/sysroot/opt/vc/lib -lmmal -lmmal_core -lmmal_util -lmmal_vc_client -lmmal_components -lvchiq_arm -lvcsm -lcontainers -lvcos -lbcm_host

#INCLUDEPATH += /home/anti/raspi/sysroot/usr/include/raspicam


# https://doc.qt.io/archives/qt-5.5/qmake-variable-reference.html#config
message(QMAKE_CC $$QMAKE_CC)
message(QMAKE_CFLAGS $$QMAKE_CFLAGS)
message(QMAKE_CXX $$QMAKE_CXX)
message(QMAKE_CXXFLAGS $$QMAKE_CXXFLAGS)
#message(QMAKE_EXT_UI $$QMAKE_EXT_UI)
contains(QMAKE_CXX,.*bcm2708.*){ message(bcm2708) }

message(OUT_PWD $$OUT_PWD)
message(QMAKESPEC $$QMAKESPEC) # /home/anti/raspi/qt5/qt5/mkspecs/devices/linux-rasp-pi4-v3d-g++
message(QT_INSTALL_PREFIX $$QT_INSTALL_PREFIX)

for(var, $$list($$enumerate_vars())) {
    message($$var)
    message($$eval($$var))
}


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# https://doc.qt.io/qt-5/qmake-manual.html
# Platform Scope Values // mkspecs -  compiler-specific values
# http://www.wiki.crossplatform.ru/index.php/Undocumented_qmake
# http://paulf.free.fr/undocumented_qmake.html
# mkspec folder: $ grep -E -o -r 'QMAKE_PLATFORM.*?$'

DISTFILES += \
    ProjectMESSAGE
