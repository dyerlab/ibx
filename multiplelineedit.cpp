/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  multiplelineedit.cpp
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

#include "multiplelineedit.h"

#include <QDebug>
#include <QHBoxLayout>

MultipleLineEdit::MultipleLineEdit(QWidget *parent) : QWidget(parent) {
    qDebug() << "In MLE::MLE";
}

void MultipleLineEdit::setText(QString text, QString sep) {
    QStringList elements;
    QHBoxLayout *horizontalLayout = new QHBoxLayout( this );
    horizontalLayout->setMargin(0);
    horizontalLayout->setSpacing(1);

    if( sep.count() > 1 )
        elements = text.split(sep);
    else
        elements.append(text);

    foreach( QString val, elements) {
        QTextEdit *edit = new QTextEdit();
        edit->setText( val );
        textEditors.append( edit );
        horizontalLayout->addWidget( edit );
    }


    qDebug() << "in setText with" << textEditors.count();
}

QStringList MultipleLineEdit::getText() const {
    QStringList ret;
    foreach( QTextEdit *edit, textEditors) {
        ret.append( edit->toPlainText() );
    }

    qDebug() << "getText";

    return ret;
}

