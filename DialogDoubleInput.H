/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DialogDoubleInput.H
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

#ifndef DIALOGDOUBLEINPUT_H
#define DIALOGDOUBLEINPUT_H

#include <QObject>
#include <QDialog>
#include <QComboBox>

class DialogDoubleInput : public QDialog
{
    Q_OBJECT
public:
    explicit DialogDoubleInput(QString title, QString msg1, QStringList items1, QString msg2, QStringList items2,  QWidget *parent  = 0);

    inline int getFirstIndex()  { return m_box1->currentIndex(); }
    inline int getSecondIndex()  { return m_box2->currentIndex(); }


private:
    QComboBox *m_box1;
    QComboBox *m_box2;
};

#endif // DIALOGDOUBLEINPUT_H
