#ifndef TABLE_ITEM_DELEGATE_H_
#define TABLE_ITEM_DELEGATE_H_


#include <QItemDelegate>
#include <QLineEdit>
#include <QWidget>

class TableItemDelegate : public QItemDelegate 
{
	Q_OBJECT

public:
	TableItemDelegate( QObject *parent=0 );
	
	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif


