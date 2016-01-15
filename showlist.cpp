#include "showlist.h"
//#include "ui_showlist.h"
#include <QtSql/QSqlDatabase>
#include <sqlite3.h>
#include <QDebug>
#include <QtSql/QSqlQueryModel>
#include <QTableView>

#include <QString>

showlist::showlist(QWidget *parent) :
    QDialog(parent)
  //,
   // ui(new Ui::showlist)
{
  //  ui->setupUi(this);
    btn_back= new QPushButton(tr("返回"));
     btn_search=new QPushButton(tr("按照类型搜索:"));
     line_name = new QLineEdit;
    show_picture();


    connect(btn_back,SIGNAL(clicked()),this,SLOT(back2before()));
    connect(btn_search,SIGNAL(clicked()),this,SLOT(searchviatype()));
}

showlist::~showlist()
{
   // delete ui;
}

void showlist::delete_show_table()
{
    static sqlite3 *db=NULL;
    char *Msg_err=NULL;
    int ok;
    ok=sqlite3_open(sql_name,&db);
    if (ok == SQLITE_OK) {
           // qDebug("Database opened sucessfully in the process of show list!\n ");
    }
    else {
            qDebug("Open database failed !  %s\n",Msg_err);
            sqlite3_close(db);
    }
    sqlite3_exec(db,"delete from data_table",NULL,NULL,&Msg_err);
}

void showlist::back2before()
{
    this->close();
}

void showlist::show_picture()
{

    table_show = new QTableWidget;
    table_show->setColumnCount(4);
    table_show->setRowCount(15);
    QStringList headers;
    headers<<"房间"<<"传感器类型"<<"网络地址"<<"数据/命令";
    table_show->setHorizontalHeaderLabels(headers);
    table_show->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_show->resizeColumnsToContents();
    QGridLayout * downLayout = new QGridLayout;
    downLayout->addWidget(btn_back,0,0,1,1);
    downLayout->addWidget(btn_search,0,2,1,1);
    downLayout->addWidget(line_name,0,3,1,2);
    downLayout->addWidget(table_show,1,0,7,5);
    downLayout->setAlignment(Qt::AlignHCenter);
    downLayout->setAlignment(Qt::AlignVCenter);

    setLayout(downLayout);
}
void showlist::show_data()
{
    table_show->clearContents();
     repaint();
     line_name->setText(NULL);
    static sqlite3 *db=NULL;
    char *Msg_err=NULL;
    static char **dbResult;
    static int nRow, nColumn,ok;

    ok=sqlite3_open(sql_name,&db);
    if (ok == SQLITE_OK) {
           // qDebug("Database opened sucessfully in the process of show list!\n ");
    }
    else {
            qDebug("Open database failed !  %s\n",Msg_err);
            sqlite3_close(db);
    }
        ok= sqlite3_get_table(db,"select * from data_table",&dbResult,&nRow,&nColumn,&Msg_err);
        for(int i=1;i<=nRow;i++) {
            QString room=dbResult[4*i];
            QString type =dbResult[4*i+1];
            QString addr = dbResult[4*i+2];
            QString data = dbResult[4*i+3];
             table_show->setItem(i-1,0,new QTableWidgetItem(room));
             table_show->setItem(i-1,1,new QTableWidgetItem(type));
             table_show->setItem(i-1,2,new QTableWidgetItem(addr));
             table_show->setItem(i-1,3,new QTableWidgetItem(data));
        }
        sqlite3_free_table(dbResult);
        sqlite3_close(db);
}

int showlist::searchviatype()
{
    table_show->clearContents();
    repaint();

    struct Data {
        int room;
        int type;
        char* addr;
        char* data;
    };
    static sqlite3 *db=NULL;
    static int nColumn, ok,j=0;
    int sensortype=line_name->text().toInt();
    Data * Datalist;
    Datalist=new Data;

    ok=sqlite3_open(sql_name,&db);
    if (ok == SQLITE_OK) {
           // qDebug("查找数据时，数据库打开正确!\n ");
    }
    else {
          //  qDebug("查找数据时，数据库打开不正确 !  %s\n",Msg_err);
        return -1;
    }


    char*  sql = (char*)"select * from data_table where sensor_type= ?";
    sqlite3_stmt  *stmt = NULL;
    ok = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);
   if (ok == SQLITE_OK) {
          // qDebug("查找数据时，得到了数据!\n ");
   }
   else {
          // qDebug("查找数据时，没有得到数据 !  %s\n",Msg_err);
       return -2;
   }
   sqlite3_bind_int(stmt,1,sensortype);
   nColumn = sqlite3_column_count(stmt);

   ok= sqlite3_step(stmt);
   while(true) {
        if (ok==SQLITE_ROW) {
            for(int i=0;i<nColumn;i++) {
                if(i==0)
                    Datalist->room  =sqlite3_column_int(stmt,i);
                if(i==1)
                     Datalist->type=sqlite3_column_int(stmt,i);
                if(i==2)
                     Datalist->addr=(char *)sqlite3_column_text(stmt,i);
                if(i==3)
                     Datalist->data=(char *)sqlite3_column_text(stmt,i);

            }
          //  qDebug("%d,%d,%s,%s\n",Datalist->room,Datalist->type,Datalist->addr,Datalist->data);
                table_show->setItem(j,0,new QTableWidgetItem(QString::number(Datalist->room,10)));
                table_show->setItem(j,1,new QTableWidgetItem(QString::number(Datalist->type,10)));
                table_show->setItem(j,2,new QTableWidgetItem(Datalist->addr));
                table_show->setItem(j,3,new QTableWidgetItem(Datalist->data));
                j++;
        }
        else if(ok==SQLITE_DONE) {
         //   qDebug("选择完成！\n");
        }
        else {
           // qDebug("错误！");
            return -3;
        }
        if (sqlite3_step(stmt) != SQLITE_ROW) {
            j=0;
            break;
         }
   }
     sqlite3_close(db);
    return 0;
}
