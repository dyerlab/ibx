#include "importgenotypesdialog.h"
#include "ui_importgenotypesdialog.h"

ImportGenotypesDialog::ImportGenotypesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportGenotypesDialog)
{
    ui->setupUi(this);
}

ImportGenotypesDialog::~ImportGenotypesDialog()
{
    delete ui;
}
