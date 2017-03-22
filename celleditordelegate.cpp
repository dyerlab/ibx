/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  genotypetableeditordelegate.cpp
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

#include "celleditordelegate.h"
#include "multiplelineedit.h"

CellEditorDelegate::CellEditorDelegate(QObject *parent) : QItemDelegate(parent) {

}



QWidget* CellEditorDelegate::createEditor( QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const {
    MultipleLineEdit *widget = new MultipleLineEdit(parent);
    return widget;
}

void CellEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QString text = index.model()->data(index,Qt::EditRole).toString();
    MultipleLineEdit *widget = static_cast<MultipleLineEdit*>(editor);
    widget->setText(text);
}


void CellEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel */*model*/, const QModelIndex &/*index*/) const {
    MultipleLineEdit *widget = static_cast<MultipleLineEdit*>(editor);
    QStringList text = widget->getText();
}

void CellEditorDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/*index*/) const {
    editor->setGeometry( option.rect );
}
