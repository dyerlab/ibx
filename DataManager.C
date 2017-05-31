/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DataManager.C
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
#include "DataManager.H"
#include "DialogImportGenotypes.H"

#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QStandardItem>

DataManager::DataManager(QStackedWidget *stackedWidget, QTreeWidget *listWidget, QObject *parent) : QObject(parent) {
    m_stackedWidget = stackedWidget;
    m_treeWidget = listWidget;
    m_treeWidget->setColumnCount(1);

    m_treeWidget->headerItem()->setText(0,tr("Data"));

    connect( m_treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
             this, SLOT(slotChangeStackedWidget(QTreeWidgetItem*,int)));
}

DataManager::~DataManager() {

}


DataBase* DataManager::topLevelItem(){
    int idx = m_stackedWidget->currentIndex();
    return( m_data.value( --idx ) );
}


void DataManager::importGenotypes() {
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

    DialogImportGenotypes *dlg = new DialogImportGenotypes(qApp->activeWindow());
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
        DataGenotypes *m_genotypes = new DataGenotypes("Genotypes");
        m_genotypes->setPopulation( thePop );
        int idx = m_stackedWidget->addWidget( m_genotypes->getWidget());
        m_genotypes->setStackIndex( idx );
        m_treeWidget->addTopLevelItem( m_genotypes->treeWidgetItem() );
        m_treeWidget->update();
        m_data.append( m_genotypes );
        slotChangeStackedWidget(m_genotypes->treeWidgetItem(), 0);

    }
    else
        delete( thePop );

}



void DataManager::slotChangeStackedWidget(QTreeWidgetItem* item ,int column) {

    Q_UNUSED(column);

    foreach( DataBase *entry, m_data ){
        if( entry->treeWidgetItem() == item ){
            int idx = entry->getStackIndex();
            m_stackedWidget->setCurrentIndex(idx);
            return;
        }
    }

    qDebug() << "You should never actually get to this point.";
}











