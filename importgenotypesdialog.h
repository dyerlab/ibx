#ifndef IMPORTGENOTYPESDIALOG_H
#define IMPORTGENOTYPESDIALOG_H

#include <QDialog>

namespace Ui {
class ImportGenotypesDialog;
}

class ImportGenotypesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportGenotypesDialog(QList<QStringList> raw, QWidget *parent = 0);
    ~ImportGenotypesDialog();

private:
    Ui::ImportGenotypesDialog *ui;
};

#endif // IMPORTGENOTYPESDIALOG_H
