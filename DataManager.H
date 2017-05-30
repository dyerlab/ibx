/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DataManager.H
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

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QTreeView>
#include <QApplication>
#include <QStackedWidget>

#include "DataGenotypes.H"

class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QStackedWidget *stackedWidget, QTreeView *listWidget, QObject *parent = 0);
    ~DataManager();

    void importGenotypes();


private:
    DataGenotypes *m_genotypes;
    QStackedWidget *m_stackedWidget;
    QTreeView *m_treeView;

};

#endif // DATAMANAGER_H
