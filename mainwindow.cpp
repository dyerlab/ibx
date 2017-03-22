/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  mainwindow.cpp
*
*  Created: 3 2017 by rodney
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

#include "factories.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileio.h"

#include <QMenu>
#include <QDebug>
#include <QSettings>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->makeActions();
    this->makeMenus();
    this->makeUI();
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    saveSettings();
    event->accept();
}

void MainWindow::loadSettings(){
    QSettings settings("DyerLab","ibx");
    move( settings.value("pos",QVariant(QPoint(100,100))).toPoint() );
    resize( settings.value( "size", QVariant(QSize(400,500))).toSize() );
    mainSplitter->restoreState( settings.value( "splitter", QVariant(QByteArray())).toByteArray());
}

void MainWindow::saveSettings(){
    QSettings settings("DyerLab","ibx");
    settings.setValue( "pos", QVariant( pos () ));
    settings.setValue( "size", QVariant( size()));
    settings.setValue( "splitter", QVariant( mainSplitter->saveState()));
}

void MainWindow::makeActions() {

    actionOpen = new QAction(tr("&Open"), this);
    actionOpen->setShortcut(tr("CTRL+O"));
    connect( actionOpen, SIGNAL(triggered(bool)), this, SLOT(slotOpen()));

    actionSave = new QAction(tr("&Save"), this);
    actionSave->setShortcut(tr("CTRL+S"));
    connect( actionSave, SIGNAL(triggered(bool)), this, SLOT(slotSave()));

    actionImport = new QAction(tr("&Import"), this);
    actionImport->setShortcut(tr("CTRL+I"));
    connect( actionImport, SIGNAL(triggered(bool)), this, SLOT(slotImport()));

    actionQuit = new QAction(tr("&Quit"), this);
    actionQuit->setShortcut(tr("CTRL+Q"));
    connect( actionQuit, SIGNAL(triggered(bool)), qApp, SLOT(closeAllWindows()));

    actionShowResults = new QAction(tr("&Results"),this);
    actionShowResults->setShortcut(tr("CTRL+R"));
    connect(actionShowResults, SIGNAL(triggered(bool)),
            this, SLOT(slotShowResults()));

    // Contextual menu for headers
    actionSetStratum = new QAction(tr("Set Stratum"),this);
    connect( actionSetStratum, SIGNAL(triggered(bool)), this, SLOT(slotSetColumnToTypeStratum()));
    actionSetCoordinates = new QAction(tr("Set Coordinates"), this);
    connect( actionSetCoordinates, SIGNAL(triggered(bool)), this, SLOT(slotSetColumnToTypeCoordinate()));
    actionSetLocus = new QAction( tr("Set Locus"), this);
    connect( actionSetLocus, SIGNAL(triggered(bool)), this, SLOT(slotSetColumnToTypeLocus()));

}

void MainWindow::makeMenus() {
    QMenu *fileMenu = this->menuBar()->addMenu(tr("&File"));

    fileMenu->addAction( actionOpen );
    fileMenu->addAction( actionSave );
    fileMenu->addSeparator();
    fileMenu->addAction( actionImport );
    fileMenu->addSeparator();
    fileMenu->addAction(actionQuit);


    QMenu *windowMenu = this->menuBar()->addMenu(tr("&Window"));
    windowMenu->addAction( actionShowResults );


}

void MainWindow::makeUI() {
    genotypeTable = new QTableView();    
    genotypeHeader = genotypeTable->horizontalHeader();
    genotypeHeader->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(genotypeHeader, SIGNAL(customContextMenuRequested(QPoint)),
    SLOT(customContextMenuRequested(QPoint)));

    cellEditorDelegate = new CellEditorDelegate( genotypeTable );
    genotypeTable->setItemDelegate( cellEditorDelegate );

    resultsView = new QWebEngineView();

    mainSplitter = new QSplitter(this);
    mainSplitter->setOrientation(Qt::Vertical);

    mainSplitter->addWidget(genotypeTable);
    mainSplitter->addWidget(resultsView);

    setCentralWidget( mainSplitter );
}


void MainWindow::slotImport(){
    QString fileName = QFileDialog::getOpenFileName(this, ("Open CSV File"),
                                                    QDir::homePath(),
                                                    ("CSV File (*.csv)"));
    if( fileName.isNull())
        return;

    QList<QStringList> data = importCSV(fileName);

    if( data.count() > 0 && data.at(0).count() > 0){
        theData = new DataSet( makeIndividualsFromCSV( data ) );
        theData->orderHeaders( data.at(0) );

        theData->getResults()->addHeader("Input Data File");
        theData->getResults()->addUnorderedList( getFileInfo(fileName) );

        dataTableModel = new DataTableModel();
        dataTableModel->setDataSet(theData);

        genotypeTable->setModel( dataTableModel );

        slotShowResults();
    }

}


void MainWindow::customContextMenuRequested(const QPoint &pos){
    QItemSelectionModel *select = genotypeTable->selectionModel();
    QModelIndexList cols = select->selectedColumns( );
    if( cols.count( ) ) {
        //int column = genotypeHeader->logicalIndexAt(pos);
        QMenu *menu = new QMenu(this);
        menu->addAction(actionSetStratum);
        menu->addAction(actionSetCoordinates);
        menu->addAction(actionSetLocus);
        menu->popup( genotypeHeader->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::setColumnToType( DATA_TYPE type ) {
    QItemSelectionModel *select = genotypeTable->selectionModel();
    QModelIndexList cols = select->selectedColumns();

    foreach( QModelIndex idx, cols ){
        int i = idx.column();
        theData->setColumnToType(i, type);
    }

    genotypeTable->clearSelection();

}

void MainWindow::slotSetColumnToTypeStratum() {
    this->setColumnToType( DATA_TYPE_STRATUM );
}

void MainWindow::slotSetColumnToTypeCoordinate() {
    this->setColumnToType( DATA_TYPE_COORDINATE );
}

void MainWindow::slotSetColumnToTypeLocus() {
    this->setColumnToType( DATA_TYPE_LOCUS );
}

void MainWindow::slotShowResults() {
    QString res = theData->getResults()->getResults();
    resultsView->setHtml(res);
    resultsView->update();
}

void MainWindow::slotOpen(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open IBX file",
                                                    QDir::currentPath(),
                                                    "IBX Files (*.ibx)");
    if( fileName.isNull())
        return;

    if( theData != NULL )
        delete theData;

    /*
    theData = loadDataSet(fileName);
    dataTableModel->setDataSet(theData);

    genotypeTable->setModel( dataTableModel );
    slotShowResults();
    */
}

void MainWindow::slotSave(){
    QString fileName = QFileDialog::getSaveFileName(this,
                                                   "Save file",
                                                   QDir::currentPath(),
                                                   "IBX Files (*.ibx)" );
    if( fileName.isNull())
        return;

/*
    if( !saveDataSet(fileName,theData)) {
        qDebug() << "Failed to save";
    }
*/


}










