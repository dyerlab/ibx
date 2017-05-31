/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  DialogDoubleInput.C
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

#include "DialogDoubleInput.H"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDialogButtonBox>


DialogDoubleInput::DialogDoubleInput(QString title, QString msg1, QStringList items1, QString msg2, QStringList items2, QWidget *parent) : QDialog(parent)
{

    QLabel *mainLabel = new QLabel( title );

    QHBoxLayout *combo1Layout = new QHBoxLayout();
    QLabel *lbl1 = new QLabel( msg1 );
    m_box1 = new QComboBox();
    m_box1->addItems( items1 );
    combo1Layout->addWidget( lbl1 );
    combo1Layout->addWidget( m_box1 );

    QHBoxLayout *combo2Layout = new QHBoxLayout();
    QLabel *lbl2 = new QLabel( msg2 );
    m_box2 = new QComboBox();
    m_box2->addItems( items2 );
    if( items1 == items2 && items2.count() > 1 )
    m_box2->setCurrentIndex( 1 );

    combo2Layout->addWidget( lbl2 );
    combo2Layout->addWidget( m_box2 );

    QDialogButtonBox *btnBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                             Qt::Horizontal,
                             this );

    connect( btnBox, SIGNAL( accepted() ), this, SLOT( accept()));
    connect( btnBox, SIGNAL( rejected() ), this, SLOT( reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget( mainLabel );
    mainLayout->addLayout( combo1Layout );
    mainLayout->addLayout( combo2Layout );
    mainLayout->addWidget( btnBox );

    setLayout( mainLayout );

}
