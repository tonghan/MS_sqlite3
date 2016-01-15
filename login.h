#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QDialog>
#include "student.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Student *stu_login;
private slots:
    void btn_click_login();
};

#endif // LOGIN_H
