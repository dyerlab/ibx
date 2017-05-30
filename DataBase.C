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

DataBase::DataBase() {
    m_type = DATA_TYPE_UNDEFINED;
    m_treeWidgetItem = new QTreeWidgetItem();
}

DataBase::~DataBase() {
    delete m_treeWidgetItem;
}

DATA_TYPE DataBase::dataType(){
    return m_type;
}

void DataBase::setLabel( QString value ) {
    m_label = value;
    m_treeWidgetItem->setText(0,m_label);
}

QString DataBase::getLabel() const {
    return m_label;
}

QTreeWidgetItem* DataBase::getTreeWidget() {
    return m_treeWidgetItem;
}

QStringList DataBase::getWarnings() {
    return m_warnings;
}
