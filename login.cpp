#include "login.h"
#include "ui_login.h"
#include "student.h"
#include "ui_student.h"
#include <QMessageBox>
#include <QAction>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   stu_login = new Student(this);
   connect(ui->btn_login,SIGNAL(clicked()),this,SLOT(btn_click_login()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btn_click_login()
{
    if ((QString::compare(ui->line_usrname->text(),"han")==0)  && (QString::compare(ui->line_passwd->text(),"123456")==0)) {
         this->hide();
         stu_login->show();
    }
    else {
       QMessageBox::StandardButton rb= QMessageBox::critical(this,"critical",tr("登录失败,重新登录"),QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
      if(rb==QMessageBox::Yes) {
          ui->line_usrname->setText(NULL);
          ui->line_passwd->setText(NULL);
          ui->line_usrname->setEnabled(true);
          ui->line_usrname->setFocus();
      }
      else {
       this->close();
      }
    }
}
