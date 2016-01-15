#ifndef ADDNUMBER_H
#define ADDNUMBER_H

#include <QDialog>
#include <QString>
#define sql_name "dataname.db"
#include <QDebug>
#include <QChar>
namespace Ui {
class addnumber;
}

class addnumber : public QDialog
{
    Q_OBJECT

public:
    explicit addnumber(QWidget *parent = 0);
    ~addnumber();
    int str_room,str_type;
    const char* str_addr;
    const char* str_data;
    void add_clear();

private:
    Ui::addnumber *ui;

private slots:
    void register_number();
    void back2before();
};

#endif // ADDNUMBER_H
