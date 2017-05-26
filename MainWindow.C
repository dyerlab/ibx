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

#include "FileIO.H"
#include "Globalz.H"
#include "MainWindow.H"
#include "DialogImportGenotypes.H"

#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>
#include <QSettings>
#include <QMenuBar>
#include <QDialog>
#include <QDebug>
#include <QLabel>
#include <QMenu>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  makeUI();
  makeActions();
  makeMenus();
  loadSettings();
  makeDataStructures();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete( theData );
}

void MainWindow::makeUI() {
  mainSplitter = new QSplitter();

  itemList = new QTreeView();
  itemList->setAlternatingRowColors(true);
  itemList->sizePolicy().setHorizontalStretch(0);
  itemList->setContextMenuPolicy( Qt::ActionsContextMenu );
  itemList->setSelectionMode( QAbstractItemView::SingleSelection );


  stackedWidget = new QStackedWidget();

  QLabel *label = new QLabel();
  label->setAutoFillBackground(true);
  label->setBackgroundRole(QPalette::Window);
  label->setAlignment(Qt::AlignCenter);
  QPixmap logo( QString(":/media/characteristic_model.png"));
  label->setPixmap( logo );
  stackedWidget->addWidget(label);

  tableView = new QTableView();
  stackedWidget->addWidget(tableView);


  mainSplitter->addWidget(itemList);
  mainSplitter->addWidget(stackedWidget);
  mainSplitter->setStretchFactor(0,0);
  mainSplitter->setStretchFactor(1,1);
  setCentralWidget(mainSplitter);
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

}

void MainWindow::makeMenus() {
  QMenu *file = this->menuBar()->addMenu(tr("&File"));
  file->addAction( importGeneticDataAction );
  file->addSeparator();
  file->addAction( quitAction );

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


void MainWindow::makeDataStructures(){
    theData = new DataSet();
}


void MainWindow::slotImportGenotypes() {
    QString fileName = QFileDialog::getOpenFileName( qApp->activeWindow(),
                                                     tr("Save GeneticStudio File"),
                                                     tr(""),
                                                     tr("Raw Genotypes (*.csv)"),
                                                     0,
                                                     QFileDialog::DontUseSheet);
    if( fileName.isEmpty() )
        return;

    QFile file(fileName);
    if( !file.open(QIODevice::ReadOnly)){
        QMessageBox messageBox;
        messageBox.setText(tr("The file requested could not be opened as a read only file."));
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.exec();
        file.close();
        return;
    }

    // grab the header;
    QTextStream stream(&file);

    QStringList headers = stream.readLine().split(",");
    if( !headers.count() ) {
        QMessageBox messageBox;
        messageBox.setText(tr("The file is supposed to be a CSV file and the first line is supposed to have column headers indicating the names of each data column."));
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.exec();
        file.close();
        return;
    }

    DialogImportGenotypes *dlg = new DialogImportGenotypes(this);
    dlg->setHeaders( headers );
    if( dlg->exec() == QDialog::Rejected ){
        delete(dlg);
        file.close();
        return;
    }

    QHash<QString,COLUMN_TYPE> columnTypes = dlg->dataTypes();
    LOCUS_TYPE locusType = dlg->getLocusType();
    delete( dlg );

    QList<QStringList> lines;
    while( !stream.atEnd()){
        lines << stream.readLine().split(",");
    }
    file.close();


    Population *thePop = importPopulationFromFile(headers,
                                                  lines,
                                                  locusType,
                                                  columnTypes);

    qDebug() << "Loaded " << thePop->count() << " individuals";

    if( thePop->count() && thePop->get(0)->numLoci() ) {
        theData->setPopulation( thePop );
        tableView->setModel( theData->getGenotypeTableModel() );
        stackedWidget->setCurrentIndex(1);
        tableView->update();
    }
    else
        delete( thePop );


}
