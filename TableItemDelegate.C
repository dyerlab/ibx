/******************************************************************************
*                       _                 _       _
*                    __| |_   _  ___ _ __| | __ _| |__
*                   / _` | | | |/ _ \ '__| |/ _` | '_ \
*                  | (_| | |_| |  __/ |  | | (_| | |_) |
*                   \__,_|\__, |\___|_|  |_|\__,_|_.__/
*                         |___/
*
*  TableItemDelegate.H
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

#include "TableItemDelegate.H"
 

TableItemDelegate::TableItemDelegate( QObject *parent ) : QItemDelegate( parent )
{
}

QWidget* TableItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
	Q_UNUSED( option );
	Q_UNUSED( index );
	
	QLineEdit *edit = new QLineEdit( parent );
	return edit;
}


void TableItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
	QLineEdit *edit = static_cast<QLineEdit*>(editor);
	edit->setText( (index.model()->data( index, Qt::DisplayRole )).toString()  );
}


void TableItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
	QLineEdit *edit = static_cast<QLineEdit*>(editor);
	QString txt = edit->text();
	if( txt.count() )
		model->setData( index, QVariant(txt), Qt::EditRole );
}


void TableItemDelegate::updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	Q_UNUSED( index );
	editor->setGeometry( option.rect );
	
}

