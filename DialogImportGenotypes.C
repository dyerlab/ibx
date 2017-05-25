/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DialogImportGenotypes.C
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

#include "DialogImportGenotypes.H"
#include "ui_DialogImportGenotypes.h"
#include <QDebug>

DialogImportGenotypes::DialogImportGenotypes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImportGenotypes)
{
    ui->setupUi(this);

    // Setting up connections
    connect(ui->strata2headers, SIGNAL(clicked(bool)),
            this, SLOT(slotStrata2Header()));
    connect(ui->headers2strata, SIGNAL(clicked(bool)),
            this, SLOT(slotHeader2Strata()));
    connect(ui->headers2external, SIGNAL(clicked(bool)),
            this, SLOT(slotHeader2External()));
    connect(ui->external2headers, SIGNAL(clicked(bool)),
            this, SLOT(slotExternal2Header()));
    connect(ui->headers2loci, SIGNAL(clicked(bool)),
            this, SLOT(slotHeader2Loci()));
    connect(ui->loci2headers, SIGNAL(clicked(bool)),
            this, SLOT(slotLoci2Header()));
}

DialogImportGenotypes::~DialogImportGenotypes()
{
    delete ui;
}


void DialogImportGenotypes::setHeaders(QStringList headers) {
    foreach( QString key, headers){
        ui->headerWidget->addItem( key );
    }
}


LOCUS_TYPE DialogImportGenotypes::getLocusType() const {
    if( ui->radio2Column->isChecked())
        return LOCUS_TYPE_2_COLUMN;
    else if( ui->radioSeparated->isChecked())
        return LOCUS_TYPE_SEPARATED;
    else if( ui->radioHaploid->isChecked())
        return LOCUS_TYPE_HAPLOID;
    else {
        qDebug() << "You should never get to this point";
        return LOCUS_TYPE_UNDEFINED;
    }
}

QHash<QString,COLUMN_TYPE> DialogImportGenotypes::dataTypes() {
    QHash<QString,COLUMN_TYPE> ret;

    for( int i=0;i<ui->strataWidget->count();i++)
        ret.insert( ui->strataWidget->item(i)->text(), COLUMN_TYPE_STRATUM );

    for( int i=0;i<ui->externalWidget->count();i++)
        ret.insert( ui->externalWidget->item(i)->text(), COLUMN_TYPE_EXTERNAL );

    for( int i=0;i<ui->lociWidget->count();i++)
        ret.insert( ui->lociWidget->item(i)->text(), COLUMN_TYPE_LOCUS );

    for( int i=0;i<ui->headerWidget->count();i++)
        ret.insert( ui->headerWidget->item(i)->text(), COLUMN_TYPE_UNDEFINED );

    return ret;
}

void DialogImportGenotypes::slotHeader2Strata() {
    foreach( QListWidgetItem *item, ui->headerWidget->selectedItems()){
        ui->strataWidget->addItem( item->text() );
        delete( item );
    }
}

void DialogImportGenotypes::slotHeader2External() {
    foreach( QListWidgetItem *item, ui->headerWidget->selectedItems()){
        ui->externalWidget->addItem( item->text() );
        delete( item );
    }
}

void DialogImportGenotypes::slotHeader2Loci() {
    foreach( QListWidgetItem *item, ui->headerWidget->selectedItems()){
        ui->lociWidget->addItem( item->text() );
        delete( item );
    }
}

void DialogImportGenotypes::slotStrata2Header() {
    foreach( QListWidgetItem *item, ui->strataWidget->selectedItems()){
        ui->headerWidget->addItem( item->text() );
        delete( item );
    }
}

void DialogImportGenotypes::slotExternal2Header() {
    foreach( QListWidgetItem *item, ui->externalWidget->selectedItems()){
        ui->headerWidget->addItem( item->text() );
        delete( item );
    }
}

void DialogImportGenotypes::slotLoci2Header() {
    foreach( QListWidgetItem *item, ui->lociWidget->selectedItems()){
        ui->headerWidget->addItem( item->text() );
        delete( item );
    }
}
