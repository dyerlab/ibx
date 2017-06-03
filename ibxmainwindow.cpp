#include "ibxmainwindow.h"
#include "ui_ibxmainwindow.h"

IBXMainWindow::IBXMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IBXMainWindow)
{
    ui->setupUi(this);
}

IBXMainWindow::~IBXMainWindow()
{
    delete ui;
}
