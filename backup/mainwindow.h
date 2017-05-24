/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  mainwindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "dataset.h"
#include "tablemodel.h"
#include "treemodel.h"

#include <QLabel>
#include <QAction>
#include <QTreeView>
#include <QSplitter>
#include <QTableView>
#include <QMainWindow>
#include <QTextBrowser>
#include <QGraphicsView>
#include <QStackedWidget>
#include <QWebEngineView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionImport;
    QAction *actionQuit;
    QAction *actionShowResults;

    QTreeView *dataTree;
    TreeModel *dataTreeModel;

    QStackedWidget *stackedWidget;

    QLabel *homeLabel;
    QLabel *viewLabel;

    QTableView *tableView;
    GenotypeTableModel *dataTableModel;

    QWebEngineView *webView;

    QTextBrowser *textBrowser;

    QGraphicsView *graphicsView;

    QSplitter *mainSplitter;

    DataSet *theData;

    void loadSettings();
    void saveSettings();
    void makeActions();
    void makeMenus();
    void makeUI();




private slots:
    void slotImport();
    void slotSave();
    void slotOpen();


};

#endif // MAINWINDOW_H
