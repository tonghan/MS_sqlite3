#ifndef SHOWLIST_H
#define SHOWLIST_H

#include <QDialog>
//#define sql_name "dataname.db"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGridLayout>
#include <QTableWidget>
#include <addnumber.h>
// namespace Ui {
//class showlist;
//}

class showlist : public QDialog
{
    Q_OBJECT

public:
    explicit showlist(QWidget *parent = 0);
    ~showlist();
    QPushButton*btn_search;
    QPushButton* btn_back ;
    QLineEdit *line_name;
    QTableWidget *table_show;
     void show_picture();
     void show_data();
//protected:
     void delete_show_table();
//private:
 //   Ui::showlist *ui;

private slots:
    void back2before();
    int searchviatype();
};

#endif // SHOWLIST_H
