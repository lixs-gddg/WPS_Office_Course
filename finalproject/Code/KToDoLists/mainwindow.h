#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "first_window.h"
#include "mytodowindow.h"
#include "mylineedit.h"
#include "groupwindow.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_first_clicked();//打开首页

    void on_pushButton_mytodo_clicked();//打开我的待办


    void on_pushButton_addgroup_clicked();//添加分组名称

    void on_pushButton_group_clicked();//打开分组

    void on_listWidget_group_itemClicked(QListWidgetItem *item);//切换分组

private:
    Ui::MainWindow *ui;
    first_window *ui_fw;
    mytodowindow *ui_mtdw;
    groupwindow *ui_gw;
};

#endif // MAINWINDOW_H
