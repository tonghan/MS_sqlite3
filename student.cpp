#include "student.h"
#include "ui_student.h"
#include <QtSql/QSqlDatabase>
#include <sqlite3.h>
#include <QMessageBox>
//#include "ui_addnumber.h"
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
//#include <QMainWindow>
Student::Student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
    add1= new addnumber(this);
    list1=new showlist(this);

    connect(ui->btn_search,SIGNAL(clicked()),this,SLOT(btn_click_search()));
    connect(ui->btn_add,SIGNAL(clicked()),this,SLOT(btn_click_add()));
    connect(ui->btn_delete,SIGNAL(clicked()),this,SLOT(btn_click_delte()));
    connect(ui->btn_help,SIGNAL(clicked()),this,SLOT(btn_click_about()));
}

Student::~Student()
{
    delete ui;
}
void Student::btn_click_about()
{
    this->close();
    QMessageBox message(QMessageBox::NoIcon,"About Author","<font color='red'>Hank  from TINGTAO  Like Maroon 5 !  Also and the luff !  ONE PIECE !!!</font>");
    message.setIconPixmap(QPixmap(":/luff.png"));
    message.exec();
    this->show();
}
void Student::btn_click_add()
{
    this->hide();
    add1->show();
    this->show();
}

void Student::btn_click_delte()
{
    this->close();
    QMessageBox::StandardButton rb=QMessageBox::warning(NULL,"warning","删除数据库？",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb==QMessageBox::Yes) {
        list1->delete_show_table();
        this->show();
    }
    else if(rb ==QMessageBox::No) {
       this->show();
    }
}

void Student::btn_click_search()
{
    list1->show();
    list1->show_data();
}
