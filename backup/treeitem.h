/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  dataitembase.h
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

#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QString>
#include <QVariant>

class TreeItem {

public:
    explicit TreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
    ~TreeItem();

    void appendChild( TreeItem *child );

    TreeItem* child( int row );
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem* parentItem();

private:
    QList<TreeItem*> children;
    QList<QVariant> contents;
    TreeItem *parent;


};

#endif // TREEITEM_H
