#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui_fw=new first_window;
    ui_mtdw=new mytodowindow;
    ui_gw=new groupwindow;
    ui->stackedWidget_UI->addWidget(ui_fw);
    ui->stackedWidget_UI->addWidget(ui_mtdw);
    ui->stackedWidget_UI->addWidget(ui_gw);
    ui->lineEdit->setPlaceholderText("输入内容后，点击上方按钮创建分组");
    ui->widget_group->setVisible(false);

    //打开数据库
    QSqlDatabase mydb=QSqlDatabase::addDatabase("QSQLITE");
    //关联数据库句柄与对应的数据库文件

    mydb.setDatabaseName(QCoreApplication::applicationDirPath()+"/mytodolist.db");
    //打开数据库
    if(!mydb.open())
    {
         qDebug()<<"数据库打开失败"<<mydb.lastError().text();
    }
    QSqlQuery query;
    QString sql="create table if not exists mtodolist3(keynum integet  PRIMARY KEY,creattime varchar(50), \
                label varchar(50),time varchar(50) ,groupname varchar(50), repeat integer,remind varchar(50) ,place varchar(50), desc varchar(50),note varchar(50), level integer, already integer);";
    if(!query.exec(sql))
    {
            qDebug()<<"sql语句执行失败:"<<query.lastError().text();
    }
    query.next();
    query.exec("SELECT count(*) FROM mtodolist3");
    query.next();
    indexkey=query.value(0).toInt();//读取数据，得到当前的indexkey数
    //获取分组名称
    query.exec("select distinct groupname from mtodolist3;");
    while (query.next())
    {
        if(query.value(0).toString()=="我的待办") continue;
        ui->listWidget_group->addItem(query.value(0).toString());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_first_clicked()
{
    ui->stackedWidget_UI->setCurrentIndex(0);
    ui->widget_group->setVisible(false);
    groupname="我的待办";
}


void MainWindow::on_pushButton_mytodo_clicked()
{
    ui->stackedWidget_UI->setCurrentIndex(1);
    ui->widget_group->setVisible(false);
    groupname="我的待办";
}


void MainWindow::on_pushButton_addgroup_clicked()
{    
    QString newgroup=ui->lineEdit->text();
    if(newgroup!="")ui->listWidget_group->addItem(newgroup);
    ui->lineEdit->setText("");
    ui->lineEdit->setPlaceholderText("输入内容后，点击上方按钮创建分组");
}

void MainWindow::on_pushButton_group_clicked()
{
    ui->stackedWidget_UI->setCurrentIndex(2);
    ui->widget_group->setVisible(true);
    groupname="我的待办";
}

void MainWindow::on_listWidget_group_itemClicked(QListWidgetItem *item)
{
    groupname=item->text();
}
