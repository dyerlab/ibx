#ifndef IBXMAINWINDOW_H
#define IBXMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class IBXMainWindow;
}

class IBXMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IBXMainWindow(QWidget *parent = 0);
    ~IBXMainWindow();

private:
    Ui::IBXMainWindow *ui;
};

#endif // IBXMAINWINDOW_H
