/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  GenotypeTableItemDelegate.C
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

#include "GenotypeTableItemDelegate.H"
#include "DoubleEdit.H"

GenotypeTableItemDelegate::GenotypeTableItemDelegate(QObject *parent) : QItemDelegate(parent) {

}

QWidget* GenotypeTableItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED( option );
    Q_UNUSED( index );
    DoubleEdit *editor = new DoubleEdit( parent );
    return editor;
}

void GenotypeTableItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QString val = index.model()->data( index, Qt::DisplayRole).toString();
    DoubleEdit *edit = static_cast<DoubleEdit*>(editor);
    edit->setText( val );
}

void GenotypeTableItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const {
    DoubleEdit *edit = static_cast<DoubleEdit*>(editor);
    model->setData( index, edit->getText()) ;
}

void GenotypeTableItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    Q_UNUSED( option );
    Q_UNUSED( index );
    editor->setGeometry( option.rect );
}
