#include "addnumber.h"
#include "ui_addnumber.h"
#include <QtSql/QSqlDatabase>
#include <sqlite3.h>
#include <QMessageBox>
#include <stdio.h>
#include <QArrayData>

addnumber::addnumber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addnumber)
{
    ui->setupUi(this);
    connect(ui->btn_add_member,SIGNAL(clicked()),this,SLOT(register_number()));
    connect(ui->btn_back,SIGNAL(clicked()),this,SLOT(back2before()));
}

addnumber::~addnumber()
{
    delete ui;

}

void addnumber::register_number()
{
    str_room=ui->line_room->text().toInt();
    str_type=ui->line_type->text().toInt();
    std::string str=ui->line_addr->text().toStdString();
    str_addr=str.c_str();
    std::string str1=ui->line_data->text().toStdString();
    str_data=str1.c_str();
    static sqlite3 *db=NULL;
    static char *Msg_err=NULL;
    static char **dbResult;
    static int nRow, nColumn,ok;
    static sqlite3_stmt *stmt = NULL; //准备语句对象

    ok=sqlite3_open(sql_name,&db);
   if(ok ==SQLITE_OK) {
      // qDebug("数据库成功打开！\n");
    }
    else {
       qDebug("数据库无法打开，请重试！\n");
        sqlite3_close(db);
    }
   ok=sqlite3_exec(db,"create table IF NOT EXISTS data_table(room int,sensor_type int,net_addr char(16) ,data char(16))",NULL,NULL,&Msg_err);
   if (ok !=SQLITE_OK ) {
       qDebug("SQL create error: %s\n",Msg_err);
   }
   else {
     //  qDebug("create table ok\n");
   }
  char* sql =(char *) "insert into data_table (room,sensor_type,net_addr,data) values (?,?,?,?)";
  ok = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);
   if (ok !=SQLITE_OK ) {
       qDebug("SQL insert error: %s\n",Msg_err);
   }
   else {
       //qDebug("insert ok\n");
   }

   sqlite3_bind_int(stmt,1,str_room);
   sqlite3_bind_int(stmt,2,str_type);
   sqlite3_bind_text(stmt,3,str_addr,strlen(str_addr),NULL);
   sqlite3_bind_text(stmt,4,str_data,strlen(str_data),NULL);
   if(sqlite3_step(stmt) != SQLITE_DONE) {
       sqlite3_finalize(stmt);
       sqlite3_close(db);
       qDebug("insert values is failed \n");
   }
   else {
      // qDebug("insert values is sucessful !\n");
       sqlite3_reset(stmt);
       sqlite3_finalize(stmt);
   }
   ok=sqlite3_get_table(db,"select * from data_table",&dbResult,&nRow,&nColumn,&Msg_err);
   if (ok !=SQLITE_OK ) {
       qDebug("SQL get table error: %s\n",Msg_err);
   }

   else {
        sqlite3_free_table(dbResult);
        add_clear();
        sqlite3_close(db);
   }

}

void addnumber::add_clear()
{
    ui->line_room->setText(NULL);
    ui->line_type->setText(NULL);
    ui->line_addr->setText(NULL);
    ui->line_data->setText(NULL);
}

void addnumber::back2before()
{
    this->hide();
}
