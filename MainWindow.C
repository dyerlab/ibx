/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  MainWindow.cpp
*
*  Created: 5 2017 by rodney
*
*  Copyright 2017 rodney.  All Rights Reserved.
*
* This file may be distributed under the terms of GNU Public License version
* 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
* license should have been included with this file, or the project in which
* this file belongs to. You may also find the details of GPL v3 at:
*
* http://www.gnu.org/licenses/gpl-3.0.txt
*
* If you have any questions regarding the use of this file, feel free to
* contact the author of this file, or the owner of the project in which
* this file belongs to.
*
******************************************************************************/


#include "Globalz.H"
#include "MainWindow.H"
#include "DialogImportGenotypes.H"

#include <QMessageBox>
#include <QCloseEvent>
#include <QSettings>
#include <QMenuBar>
#include <QDialog>
#include <QDebug>
#include <QLabel>
#include <QMenu>
#include <ctime>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    makeUI();
    makeActions();
    makeMenus();
    loadSettings();

    // Set up the global random number generator
    if( rng == NULL ) {
        const gsl_rng_type *T;
        gsl_rng_env_setup();
        T = gsl_rng_default;
        rng = gsl_rng_alloc( T );
        gsl_rng_set( rng, time(NULL) );
    }



}

MainWindow::~MainWindow() {
    saveSettings();
}

void MainWindow::makeUI() {
    mainSplitter = new QSplitter();

    treeWidget = new QTreeWidget();
    treeWidget->setAlternatingRowColors(true);
    treeWidget->sizePolicy().setHorizontalStretch(0);
    treeWidget->setContextMenuPolicy( Qt::ActionsContextMenu );
    treeWidget->setSelectionMode( QAbstractItemView::SingleSelection );

    stackedWidget = new QStackedWidget();

    QLabel *label = new QLabel();
    label->setAutoFillBackground(true);
    label->setBackgroundRole(QPalette::Window);
    label->setAlignment(Qt::AlignCenter);
    QPixmap logo( QString(":/media/characteristic_model.png"));
    label->setPixmap( logo );
    stackedWidget->addWidget(label);
    connect( stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(slotStackedWidgetChanged(int)));


    mainSplitter->addWidget(treeWidget);
    mainSplitter->addWidget(stackedWidget);
    mainSplitter->setStretchFactor(0,0);
    mainSplitter->setStretchFactor(1,1);
    setCentralWidget(mainSplitter);

    // Make the data
    theData = new DataManager(stackedWidget,treeWidget );
}

void MainWindow::makeActions() {
    importGeneticDataAction = new QAction( tr("Genotypes"), this);
    importGeneticDataAction->setShortcut(tr("CTRL+I"));
    connect( importGeneticDataAction, SIGNAL(triggered(bool)),
             this, SLOT(slotImportGenotypes()));

    quitAction = new QAction( tr("&Quit"), this );
    quitAction->setShortcut(tr("CTRL+Q"));
    connect( quitAction, SIGNAL( triggered() ),
             qApp, SLOT( closeAllWindows() ) );

    nextDataAction = new QAction(tr("Next"), this);
    prevDataAction = new QAction(tr("Previsou"), this);

    alleleFrequencyAction = new QAction( tr("Allele Frequencies"), this);
    alleleFrequencyAction->setShortcut(tr("CTRL+F"));


}

void MainWindow::makeMenus() {
    QMenu *file = this->menuBar()->addMenu(tr("&File"));
    file->addAction( importGeneticDataAction );
    file->addSeparator();
    file->addAction( quitAction );

    QMenu *view = this->menuBar()->addMenu( tr("&View"));
    view->addAction( nextDataAction );
    view->addAction( prevDataAction );

    QMenu *analyses = this->menuBar()->addMenu(tr("&Analyses"));
    analyses->addAction( alleleFrequencyAction );

}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveSettings();
    event->accept();
}

void MainWindow::loadSettings() {
    QSettings settings("Dyerlab","ibx");
    QRect rect = settings.value("geometry",QVariant(QRect(100,100,400,600))).toRect();
    move( rect.topLeft() );
    resize( rect.size() );
    mainSplitter->restoreState( settings.value("mainSplitter").toByteArray());
}

void MainWindow::saveSettings() {
    QSettings settings("Dyerlab","ibx");
    settings.setValue("geometry",QVariant( geometry() ));
    settings.setValue("mainSplitter",QVariant(mainSplitter->saveState()));
}




/******************************************************************
 *                                                                *
 *                         SIGNALS & SLOTS                        *
 *                                                                *
 ******************************************************************/

void MainWindow::slotImportGenotypes(){
    theData->importGenotypes();
}


void MainWindow::slotStackedWidgetChanged(int) {
    DATA_TYPE type = theData->topLevelItem()->dataType();


    if( type == DATA_TYPE_GENOTYPES ){

    }


    else if( type == DATA_TYPE_RESULTS ){

    }


}
