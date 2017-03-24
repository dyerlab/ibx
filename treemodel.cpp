/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  dataitemmodel.cpp
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

#include <QDebug>
#include "treemodel.h"

TreeModel::TreeModel(QObject *parent) : QAbstractItemModel(parent) {
    QList<QVariant> headers;
    headers << "Data";

    rootItem = new TreeItem(headers);

}


TreeModel::~TreeModel(){
    delete rootItem;
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if( !hasIndex(row,column,parent))
        return QModelIndex();

    TreeItem *parentItem;
    if( !parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *child = parentItem->child(row);
    if( child )
        return createIndex(row,column,child);
    else
        return QModelIndex();

}



QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if( !index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if( parentItem == rootItem )
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem );
}


int TreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parentItem;
    if( parent.column() > 0)
        return 0;

    if( !parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &parent) const {
    if( parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}



QVariant TreeModel::data( const QModelIndex &index, int role) const {
    if( !index.isValid())
        return QVariant();
    if( role != Qt::DisplayRole)
        return QVariant();
    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if( !index.isValid())
        return 0;
    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}



