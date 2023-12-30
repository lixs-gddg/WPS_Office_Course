#ifndef FIRST_WINDOW_H
#define FIRST_WINDOW_H

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
#include "mylineedit.h"
#include "data_struct.h"
#include "mycalendarwidget.h"
#include "remindcalendarwidget.h"
namespace Ui {
class first_window;
}

class first_window : public QWidget
{
    Q_OBJECT

public:
    explicit first_window(QWidget *parent = nullptr);
    ~first_window();
private slots:
    void lineEditClicked();//点击输入待办

    void on_lineEdit_newtodo_returnPressed();//添加待办

    void on_treeWidget_todolists_itemClicked(QTreeWidgetItem *item, int column);//选择待办

    void on_comboBox_currentIndexChanged(int index);//选择优先级

    void on_label_dtime_clicked();//打开到期时间选择框

    void on_label_remindtime_clicked();//打开提醒时间选择框

    void on_textEdit_desc_textChanged();//修改描述

    void on_textEdit_place_textChanged();//修改地点

    void on_textEdit_note_textChanged();//修改备注

    void reflashdtime(QDate dtime,int repeat);//刷新到期时间

    void reflashremindtime(QDate retime,QTime retimed);//刷新提醒时间

    void reflashall();//刷新目前选择的待办在TreeWidget中的显示

    void reflashItems(todoitem &i);//刷新待办i在TreeWidget中的显示

    void on_pushButton_clicked();//刷新TreeWidget

    void additemtodb(todoitem i);//添加待办到数据库中

    void updateitemtodb(todoitem i,int q);//更新待办数据，q表示是否完成

signals:
    void  senddtime(QDate dtime,int repeat);//返回选择的到期时间

    void  sendremindtime(QDate retime,QTime retimed);//返回选择的提醒时间

private:
    Ui::first_window *ui;
    QString newtodo;
    std::vector<todoitem> mytodoitem; //存储待办
    QList<QTreeWidgetItem *> items; //存储4个头结点
    int indexnum=0;
    mycalenderwidget *c1;
    remindcalendarwidget *c2;
};

#endif // FIRST_WINDOW_H
