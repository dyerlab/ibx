/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DoubleEdit.C
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

#include "DoubleEdit.H"

#include <QStringList>
#include <QHBoxLayout>


DoubleEdit::DoubleEdit(QWidget *parent) : QWidget(parent) {
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    leftEdit = new QLineEdit();
    rightEdit = new QLineEdit();
    mainLayout->addWidget(leftEdit);
    mainLayout->addWidget(rightEdit);
}

void DoubleEdit::setText(QString txt){
    QStringList alleles = txt.split(":", QString::SkipEmptyParts);

    leftEdit->setVisible(true);
    rightEdit->setVisible(true);
    leftEdit->setEnabled(true);
    rightEdit->setEnabled(true);

    if( alleles.count() == 1 ){
        leftEdit->setText( alleles[0] );
        rightEdit->setVisible(false);
        rightEdit->setEnabled(false);
    }
    else if( alleles.count() == 2 ){
        leftEdit->setText( alleles[0] );
        rightEdit->setText(alleles[1] );
    }
    else if( alleles.count() > 2 ){
        leftEdit->setText(txt);
        rightEdit->setVisible(false);
        rightEdit->setEnabled(false);
    }

}



QString DoubleEdit::getText() {
    QStringList ret;
    ret << leftEdit->text();
    ret << rightEdit->text();
    return ret.join(":");
}


bool DoubleEdit::focusNextPrevChild ( bool next ) {
    if( next ){
        if( leftEdit->hasFocus() ) {
            rightEdit->setFocus();
            return true;
        }

    } else {
        if( rightEdit->hasFocus() ){
            leftEdit->setFocus();
            return true;
        }
    }
    return false;
}
