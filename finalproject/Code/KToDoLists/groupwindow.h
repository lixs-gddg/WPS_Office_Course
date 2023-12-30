#ifndef GROUPWINDOW_H
#define GROUPWINDOW_H

#include <QWidget>
#include <QList>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QString>
#include <QDebug>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <vector>
#include <iostream>
#include <QCalendarWidget>
#include <QPixmap>
#include "mylineedit.h"
#include "data_struct.h"
#include "mycalendarwidget.h"
#include "remindcalendarwidget.h"
namespace Ui {
class groupwindow;
}

class groupwindow : public QWidget
{
    Q_OBJECT

public:
    explicit groupwindow(QWidget *parent = nullptr);
    ~groupwindow();

private slots:
    void lineEditClicked();//点击输入待办

    void on_lineEdit_newtodo_returnPressed();//新建待办

    void on_listWidget_todolists_itemClicked(QListWidgetItem *item);//选择待办

    void reflashall();//刷新当前待办在ListWidget中的显示

    void on_comboBox_currentIndexChanged(int index);//选择优先级

    void on_label_dtime_clicked();//选择到期时间

    void reflashdtime(QDate dtime,int repeat);//刷新到期时间

    void reflashremindtime(QDate retime,QTime retimed);//刷新提醒时间

    void on_label_remindtime_clicked();//选择提醒时间

    void on_textEdit_desc_textChanged();//修改描述

    void on_textEdit_place_textChanged();//修改地点

    void on_textEdit_note_textChanged();//修改备注

    void reflashItems(todoitem &i);//刷新待办i在ListWidget中的显示

    void on_comboBox_2_currentIndexChanged(int index);//选择排序方式

    void on_pushButton_clicked();//刷新ListWidget

    void additemtodb(todoitem i);//添加待办到数据库

    void updateitemtodb(todoitem i,int q);//更新数据

    void on_pushButton_2_clicked(bool checked);//展开已完成

    void addalreadyitem();//刷新已完成待办

    void reflashalreadyitem(todoitem &i);//刷新已完成待办在ListWidget中的显示

    void on_listWidget_itemClicked(QListWidgetItem *item);//选择已完成待办

signals:
    void  senddtime(QDate dtime,int repeat);

    void  sendremindtime(QDate retime,QTime retimed);

private:
    Ui::groupwindow *ui;
    QString newtodo;
    std::vector<todoitem> mytodoitem3;//当前分组待办
    int indexnum3=0;
    mycalenderwidget *c1;
    remindcalendarwidget *c2;
    std::vector<todoitem> alreadyitem3;//当前分组已完成待办
};

#endif // GROUPWINDOW_H
