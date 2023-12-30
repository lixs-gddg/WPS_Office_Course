#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
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
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
typedef struct todoitem{
    QString label;
    QString time="未安排";
    QString group="我的待办";
    int Repeat=0;
    QString remind="未安排";
    QString place="无";
    QString description="无";
    QString note="无";
    QTreeWidgetItem *item;//树形
    QListWidgetItem *item2;//列形
    int level=0;
    int we=0;
    QDateTime createTime;
    int key;
}todoitem;
extern QString groupname;//当前选中的组名
extern int indexkey;//当前的待办在数据库中的编号
#endif // DATA_STRUCT_H
