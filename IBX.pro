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


SOURCES += main.cpp\
        mainwindow.cpp \
    fileio.cpp \
    individual.cpp \
    dataset.cpp \
    factories.cpp \
    resultsdocument.cpp \
    spatialindividual.cpp \
    multiplelineedit.cpp \
    treeitem.cpp \
    tablemodel.cpp \
    treemodel.cpp \
    population.cpp \
    importgenotypesdialog.cpp

HEADERS  += mainwindow.h \
    fileio.h \
    individual.h \
    dataset.h \
    factories.h \
    resultsdocument.h \
    spatialindividual.h \
    multiplelineedit.h \
    globalz.h \
    treeitem.h \
    tablemodel.h \
    treemodel.h \
    population.h \
    importgenotypesdialog.h

FORMS    += mainwindow.ui \
    importgenotypesdialog.ui

DISTFILES += \
    media/characteristic_model.png \
    LICENSE \
    README.md \
    AppStyleSheet.css

RESOURCES += \
    ibx.qrc

OTHER_FILES += \
    media/map_base.html \
    media/blank_page.html \
    media/GSLogo.png \
    AppStyleSheet.css \
    media/ResultsStyleSheet.css
