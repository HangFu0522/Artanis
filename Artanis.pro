#-------------------------------------------------
#
# Project created by QtCreator 2019-07-01T11:28:58
#
#-------------------------------------------------

QT       += core gui charts
CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Artanis
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    3rdpackage/csv.h \
    3rdpackage/matfile.h \
    Analyze/analyze.h \
    Analyze/fit.h \
    Base/base.h \
    Chart/common.h \
    Data/beadData.h \
    Data/onebead.h \
    Data/onebeaddata_org.h \
    Data/onebeaddata_view.h \
    GUI/chartcontrol.h \
    GUI/customtabstyle.h \
    GUI/forceextensionchart.h \
    GUI/magneticfieldparameter.h \
    GUI/mainwindow.h \
    GUI/optiongui.h \
    GUI/piecegui.h \
    Chart/chartcontrol.h \
    Chart/chart.h \
    Chart/chartview.h \
    Analyze/analyze.h \
    Analyze/fit.h \


SOURCES += \
    3rdpackage/matfile.cpp \
    Base/base.cpp \
    Chart/common.cpp \
    Data/beadData.cpp \
    Data/onebead.cpp \
    Data/onebeaddata_org.cpp \
    Data/onebeaddata_view.cpp \
    main.cpp \
    GUI/forceextensionchart.cpp \
    GUI/magneticfieldparameter.cpp \
    GUI/mainwindow.cpp \
    GUI/optiongui.cpp \
    GUI/piecegui.cpp \
    Chart/chartcontrol.cpp \
    Chart/chart.cpp \
    Chart/chartview.cpp

FORMS += \
    GUI/forceextensionchart.ui \
    GUI/mainwindow.ui \
    GUI/optiongui.ui \
    GUI/piecegui.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


LIBS += -L$$PWD/'../../../../../Program Files/MATLAB/R2018b/extern/lib/win64/microsoft/' -llibeng
LIBS += -L$$PWD/'../../../../../Program Files/MATLAB/R2018b/extern/lib/win64/microsoft/' -llibmx
LIBS += -L$$PWD/'../../../../../Program Files/MATLAB/R2018b/extern/lib/win64/microsoft/' -llibmex
LIBS += -L$$PWD/'../../../../../Program Files/MATLAB/R2018b/extern/lib/win64/microsoft/' -llibmat


INCLUDEPATH += $$PWD/'../../../../../Program Files/MATLAB/R2018b/extern/include'
DEPENDPATH += $$PWD/'../../../../../Program Files/MATLAB/R2018b/extern/include'
INCLUDEPATH += $$PWD/'../../../../../Program Files/MATLAB/R2018b/extern/include/win64'
DEPENDPATH += $$PWD/'../../../../../Program Files/MATLAB/R2018b/extern/include/win64'
