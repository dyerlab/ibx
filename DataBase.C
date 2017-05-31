/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DataBase.C
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

#include "DataBase.H"
#include <QTreeWidgetItem>

DataBase::DataBase(QString label, DataBase *parent) {
    m_parent = parent;
    m_label = label;
    m_type = DATA_TYPE_UNDEFINED;
    m_treeWidgetItem = new QTreeWidgetItem(QStringList(m_label));
}

DataBase::~DataBase() {
    qDeleteAll( m_children );
    delete m_treeWidgetItem;
}

void DataBase::setLabel( QString label ) {
    m_treeWidgetItem->setText(0,label);
}

void DataBase::setToolTip(QString label) {
    m_treeWidgetItem->setToolTip(0, label );
}

DATA_TYPE DataBase::dataType(){
    return m_type;
}

QStringList DataBase::getWarnings() {
    return m_warnings;
}


/*******************   Tree View Overrides ************/

void DataBase::appendChild(DataBase *child) {
    child->m_parent = this;
    m_treeWidgetItem->addChild( child->m_treeWidgetItem );
    m_children.append(child);
}



DataBase* DataBase::child( int idx ){
    return m_children.value(idx);
}

