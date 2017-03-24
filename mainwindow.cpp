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


#include "mainwindow.h"

#include "importgenotypesdialog.h"

#include "fileio.h"
#include "globalz.h"
#include "factories.h"
#include "ui_mainwindow.h"


#include <QMenu>
#include <QDebug>
#include <QLabel>
#include <QSettings>
#include <QVBoxLayout>
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

    QFile in(":/AppStyleSheet.css");
    if( in.open(QIODevice::Text|QIODevice::ReadOnly)) {
        QTextStream stream(&in);
        QString sheet = stream.readAll();
        if( !sheet.isEmpty() )
            this->setStyleSheet( sheet );
        in.close();
    } else {
        qDebug() << "Could not load style sheet.";
    }

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


}

void MainWindow::makeMenus() {
    QMenu *fileMenu = this->menuBar()->addMenu(tr("&File"));

    fileMenu->addAction( actionOpen );
    fileMenu->addAction( actionSave );
    fileMenu->addSeparator();
    fileMenu->addAction( actionImport );
    fileMenu->addSeparator();
    fileMenu->addAction(actionQuit);


}

void MainWindow::makeUI() {
    mainSplitter = new QSplitter();
    mainSplitter->setOrientation( Qt::Horizontal );

    // Data List (left side)
    QWidget *dataWidget = new QWidget();
    dataWidget->setObjectName("bordered");
    QVBoxLayout *dataLayout = new QVBoxLayout( dataWidget );
    dataLayout->setObjectName("slimLayout");
    dataLayout->setSpacing(0);
    dataLayout->setMargin(0);
    QLabel *dataLabel = new QLabel(tr("d a t a"));
    dataLabel->setFixedHeight( 25 );
    dataLabel->setObjectName("titleLabel");

    // make the data tree
    dataTree = new QTreeView();
    dataTree->setAttribute(Qt::WA_MacShowFocusRect, false);
    dataTree->setHeaderHidden(true);
    dataTree->setSelectionMode(QAbstractItemView::SingleSelection);
    dataTree->setObjectName("dataTree");
    dataTreeModel = new TreeModel();
    dataTree->setModel( dataTreeModel );

    dataLayout->addWidget( dataLabel );
    dataLayout->addWidget( dataTree );

    // Right side
    QWidget *viewWidget = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout( viewWidget );
    rightLayout->setMargin(0);
    rightLayout->setSpacing(0);
    viewLabel = new QLabel(tr(""));
    viewLabel->setFixedHeight(25);
    viewLabel->setObjectName("titleLabel");

    stackedWidget = new QStackedWidget();
    stackedWidget->setMinimumWidth(650);
    stackedWidget->setMinimumHeight(500);
    rightLayout->addWidget( viewLabel );
    rightLayout->addWidget( stackedWidget );

    tableView = new QTableView();

    webView = new QWebEngineView();

    homeLabel = new QLabel();
    homeLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    homeLabel->setScaledContents(false);
    homeLabel->setAlignment(Qt::AlignCenter|Qt::AlignHCenter);

    textBrowser = new QTextBrowser();
    textBrowser->setAcceptRichText(true);
    textBrowser->setContentsMargins(5,5,5,5);
    textBrowser->setReadOnly(true);

    graphicsView = new QGraphicsView();

    stackedWidget->addWidget( homeLabel );
    stackedWidget->addWidget( textBrowser );
    stackedWidget->addWidget( webView );
    stackedWidget->addWidget( tableView );
    stackedWidget->addWidget( graphicsView );
    stackedWidget->setCurrentIndex( MAIN_WIDGET_HOME );

    mainSplitter->addWidget( dataWidget );
    mainSplitter->addWidget( viewWidget );


    setCentralWidget( mainSplitter );
    mainSplitter->setFocus();
}


void MainWindow::slotImport(){

    QString fileName = QFileDialog::getOpenFileName(this, ("Open CSV File"),
                                                    QDir::homePath(),
                                                    ("CSV File (*.csv)"));
    if( fileName.isNull())
        return;

    QList<QStringList> raw = importCSV(fileName);
    if( !raw.count() )
        return;

    ImportGenotypesDialog *dlg = new ImportGenotypesDialog(raw, this);


    if( dlg->exec() == QDialog::Accepted )
        qDebug() << "YES";
    else
        qDebug() << "NO";

    delete( dlg );
    /*


    QList<QStringList> data = importCSV(fileName);

    if( data.count() > 0 && data.at(0).count() > 0){

        theData = new DataSet();


        theData->orderHeaders( data.at(0) );

        theData->getResults()->addHeader("Input Data File");
        theData->getResults()->addUnorderedList( getFileInfo(fileName) );

        dataTableModel = new GenotypeTableModel();
        dataTableModel->setDataSet(theData);
        tableView->setModel( dataTableModel );


    }

    */

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

    tableView->setModel( dataTableModel );

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










