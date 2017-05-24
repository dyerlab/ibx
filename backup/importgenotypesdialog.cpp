#include "importgenotypesdialog.h"
#include "ui_importgenotypesdialog.h"



ImportGenotypesDialog::ImportGenotypesDialog(QList<QStringList> raw, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportGenotypesDialog)
{
    ui->setupUi(this);
}

ImportGenotypesDialog::~ImportGenotypesDialog()
{
    delete ui;
}
