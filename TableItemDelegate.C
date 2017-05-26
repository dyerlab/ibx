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

