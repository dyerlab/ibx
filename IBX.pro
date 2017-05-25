#-------------------------------------------------
#
# Project created by QtCreator 2017-03-16T08:46:42
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IBX
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    MainWindow.C \
    Locus.C \
    Individual.C \
    Population.C \
    FileIO.C \
    DialogImportGenotypes.C

HEADERS  += \
    MainWindow.H \
    Locus.H \
    Globalz.H \
    Individual.H \
    Population.H \
    FileIO.H \
    DialogImportGenotypes.H

FORMS    += \
    DialogImportGenotypes.ui

DISTFILES += \
    media/characteristic_model.png \
    LICENSE \
    README.md \
    AppStyleSheet.css

RESOURCES += \
    ibx.qrc

OTHER_FILES += \
    AppStyleSheet.css
