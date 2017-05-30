/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  MainWindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>
#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QSplitter>
#include <QTreeView>
#include <QAction>

#include "DataManager.H"



class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

signals:

public slots:

    void slotImportGenotypes();

private:


  DataManager *theData;

  QSplitter *mainSplitter;

  QTreeView *treeView;

  QStackedWidget *stackedWidget;
  QTableView *tableView;

  QAction *quitAction;
  QAction *importGeneticDataAction;


  void makeUI();
  void makeActions();
  void makeMenus();

  void closeEvent(QCloseEvent *event) override;
  void loadSettings();
  void saveSettings();

};

#endif // MAINWINDOW_H
