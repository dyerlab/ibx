/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DataBase.H
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

#ifndef DATABASE_H
#define DATABASE_H

#include "Globalz.H"

#include <QFile>
#include <QDebug>
#include <QString>
#include <QWidget>
#include <QTextStream>
#include <QStringList>
#include <QApplication>
#include <QTreeWidgetItem>


class DataBase
{
public:
    DataBase(QString label, DataBase *parent = 0 );
    ~DataBase();

    void setLabel( QString label );
    void setToolTip( QString label );

    DATA_TYPE dataType();
    inline QWidget* getWidget() {return new QWidget(); }
    inline void setStackIndex(int val ) { m_stack_index = val; }
    inline int getStackIndex() const { return m_stack_index; }

    QStringList getWarnings();

    // overrides for tree item
    void appendChild( DataBase *child );
    DataBase* child( int idx );
    inline int childCount() const               { return m_children.count(); }
    inline QTreeWidgetItem* treeWidgetItem()    {return m_treeWidgetItem; }


protected:
    DataBase *m_parent;
    QList<DataBase*> m_children;
    QTreeWidgetItem *m_treeWidgetItem;

    int m_stack_index;
    DATA_TYPE m_type;
    QString m_label;
    QStringList m_warnings;


    void setParent( DataBase *parent );



};

#endif // DATABASE_H
