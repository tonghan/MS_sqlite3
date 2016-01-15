#ifndef STUDENT_H
#define STUDENT_H

#include <QDialog>
#include "addnumber.h"
#include "showlist.h"
#include <QMainWindow>

namespace Ui {
class Student;
}

class Student : public QDialog
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = 0);
    ~Student();

private:
    Ui::Student *ui;
    addnumber *add1;
    showlist  *list1;
private slots:
    void btn_click_search();
    void btn_click_add();
    void btn_click_delte();
    void btn_click_about();
};

#endif // STUDENT_H
