/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  dataitembase.cpp
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

#include "globalz.h"
#include "treeitem.h"

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent) {
    this->parent = parent;
    this->contents = data;
}

TreeItem::~TreeItem() {
    qDeleteAll( children );
}

void TreeItem::appendChild( TreeItem *child ) {
    children.append( child );
}

TreeItem* TreeItem::child( int row ) {
    return children.value(row);
}

int TreeItem::childCount() const {
    return children.count();
}

int TreeItem::columnCount() const {
    return this->contents.count();
}

QVariant TreeItem::data(int column) const {
    return this->contents.value(column);
}


int TreeItem::row() const {
    if( parent )
        return parent->children.indexOf( const_cast<TreeItem*>(this) );
    return 0;
}


TreeItem* TreeItem::parentItem() {
    return this->parent;
}
