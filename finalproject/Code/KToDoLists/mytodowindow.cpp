#include "mytodowindow.h"
#include "ui_mytodowindow.h"

mytodowindow::mytodowindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mytodowindow)
{
    ui->setupUi(this);
    ui->lineEdit_newtodo->setStyleSheet("color:green");
    connect(ui->lineEdit_newtodo, SIGNAL(clicked()), this, SLOT(lineEditClicked()));
    ui->widget->setVisible(false);
    c1=new mycalenderwidget(ui->widget);
    c1->hide();
    connect(c1,SIGNAL(senddtime(QDate,int)),this,SLOT(reflashdtime(QDate,int)));
    c2=new remindcalendarwidget(ui->widget);
    c2->hide();
    connect(c2,SIGNAL(sendremindtime(QDate,QTime)),this,SLOT(reflashremindtime(QDate,QTime)));
    ui->listWidget->setVisible(false);
    ui->pushButton_2->setCheckable(true);
    ui->widget_2->setVisible(false);
}

mytodowindow::~mytodowindow()
{
    delete ui;
}

void mytodowindow::lineEditClicked() {
    ui->lineEdit_newtodo->setText("");
    ui->lineEdit_newtodo->setStyleSheet("color:black");
    ui->lineEdit_newtodo->setPlaceholderText("输入内容后，回车创建成功");
}

void mytodowindow::on_lineEdit_newtodo_returnPressed()
{
    newtodo=ui->lineEdit_newtodo->text();
    ui->lineEdit_newtodo->setStyleSheet("color:green");
    ui->lineEdit_newtodo->setText("+ 新建待办");
    ui->listWidget_todolists->setFocus();//让输入框失去焦点
    todoitem newitem;
    newitem.label=newtodo;
    newitem.createTime=QDateTime::currentDateTime();
    qDebug()<<indexkey;
    newitem.key=indexkey++;
    QListWidgetItem *item=new QListWidgetItem;
    item->setSizeHint(QSize(1100, 80));
    ui->listWidget_todolists->addItem(item);
    QWidget *w=new QWidget;
    QLabel *lab=new QLabel;
    QLabel *timelab=new QLabel;
    QLabel *repeatlab=new QLabel;
    QLabel *grouplab=new QLabel;
    QLabel *fglab=new QLabel;
    QLabel *fglab2=new QLabel;
    timelab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    timelab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    timelab->setText("未安排");
    repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    repeatlab->setText("不重复");
    grouplab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    grouplab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    grouplab->setText("我的待办");
    fglab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab->setText("|");
    fglab2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab2->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab2->setText("|");
    lab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    lab->setText(newtodo);
    QCheckBox *checkBox=new QCheckBox(w);
    QGridLayout *layout=new QGridLayout;
    layout->setSpacing(10);
    layout->addWidget(checkBox,0,0,1,1);
    layout->addWidget(lab,0,1,1,15);
    layout->addWidget(timelab,1,0,1,1);
    layout->addWidget(fglab,1,1,1,1);
    layout->addWidget(repeatlab,1,2,1,1);
     layout->addWidget(fglab2,1,3,1,1);
    layout->addWidget(grouplab,1,4,1,1);
    w->setLayout(layout);
    ui->listWidget_todolists->setItemWidget(item,w);
    newitem.item2=item;
    mytodoitem2.push_back(newitem);
    connect(checkBox,&QCheckBox::clicked, [=](){
        qDebug()<<"信号点击";
        auto i=mytodoitem2.begin();
        for(;i!=mytodoitem2.end();i++)
        {
            if(item==i->item2)
            {
                qDebug()<<i->label;
                updateitemtodb(*i,0);
                break;
            }
        }
        mytodoitem2.erase(i);
        ui->widget->setVisible(false);
        delete item;
        });
    additemtodb(newitem);
}


void mytodowindow::on_listWidget_todolists_itemClicked(QListWidgetItem *item)
{
    bool flag=true;
    auto i=mytodoitem2.begin();
    for(indexnum2=0;i!=mytodoitem2.end();i++,indexnum2++)
    {
        if(item==i->item2)
        {
            qDebug()<<i->label;
            flag=false;
            break;
        }
    }
    if(flag) return;
    ui->widget->setVisible(true);
    ui->label_todoname->setText(i->label);
    switch(i->level)
    {
    case 0:    ui->comboBox->setCurrentText("无优先级");
               break;
    case 1:    ui->comboBox->setCurrentText("低");
               break;
    case 2:    ui->comboBox->setCurrentText("中");
               break;
    case 3:    ui->comboBox->setCurrentText("高");
               break;
    }
    if(i->time=="未安排")
    {
         ui->label_dtime->setText("设置到期时间");
    }
    else
    {
        ui->label_dtime->setText(i->time);
    }
    if(i->remind=="未安排")
     {
        ui->label_remindtime->setText("设置提醒");
    }
    else
    {
         ui->label_remindtime->setText(i->remind);
    }
    if(i->description=="无")
    {
        ui->textEdit_desc->setText("");
        ui->textEdit_desc->setPlaceholderText("添加描述");
    }
    else
    {
        ui->textEdit_desc->setText(i->description);
    }
    if(i->place=="无")
    {
        ui->textEdit_place->setText("");
        ui->textEdit_place->setPlaceholderText("添加地点");
    }
    else
    {
        ui->textEdit_place->setText(i->place);
    }
    if(i->note=="无")
    {
        ui->textEdit_note->setText("");
        ui->textEdit_note->setPlaceholderText("添加备注");
    }
    else
    {
        ui->textEdit_note->setText(i->note);
    }
}

void mytodowindow::reflashall()
{
    delete  mytodoitem2[indexnum2].item2;
    QListWidgetItem *item=new QListWidgetItem;
    item->setSizeHint(QSize(1100, 80));
    ui->listWidget_todolists->addItem(item);
    QWidget *w=new QWidget;
    QLabel *lab=new QLabel;
    QLabel *levellab=new QLabel;
    QLabel *timelab=new QLabel;
    QLabel *repeatlab=new QLabel;
    QLabel *remindlab=new QLabel;
    QLabel *grouplab=new QLabel;
    QLabel *fglab=new QLabel;
    QLabel *fglab2=new QLabel;
    QLabel *fglab3=new QLabel;
    timelab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    timelab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    timelab->setText(mytodoitem2[indexnum2].time);
    repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    switch(mytodoitem2[indexnum2].Repeat)
    {
    case 0:repeatlab->setText("不重复");
           break;
    case 1:repeatlab->setText("每天重复");
           break;
    case 2:repeatlab->setText("每周重复");
           break;
    case 3:repeatlab->setText("每月重复");
           break;
    }
    QPixmap pix;
    switch(mytodoitem2[indexnum2].level)
    {
    case 1:pix.load(":/image/low.png");
        break;
    case 2:pix.load(":/image/mid.png");
        break;
    case 3:pix.load(":/image/high.png");
        break;
    }
    levellab->setPixmap(pix);
    grouplab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    grouplab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    grouplab->setText(mytodoitem2[indexnum2].group);
    remindlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    remindlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    remindlab->setText(mytodoitem2[indexnum2].remind);
    fglab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab->setText("|");
    fglab2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab2->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab2->setText("|");
    fglab3->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab3->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab3->setText("|");
    lab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    lab->setText(mytodoitem2[indexnum2].label);
    QCheckBox *checkBox=new QCheckBox(w);
    QGridLayout *layout=new QGridLayout;
    layout->setSpacing(10);
    if(mytodoitem2[indexnum2].level)
    {
        layout->addWidget(checkBox,0,0,1,1);
        layout->addWidget(levellab,0,1,1,1);
        layout->addWidget(lab,0,2,1,15);
    }
    else
    {
        layout->addWidget(checkBox,0,0,1,1);
        layout->addWidget(lab,0,1,1,15);
    }
    if(mytodoitem2[indexnum2].remind=="未安排")
    {
        layout->addWidget(timelab,1,0,1,1);
        layout->addWidget(fglab,1,1,1,1);
        layout->addWidget(repeatlab,1,2,1,1);
        layout->addWidget(fglab2,1,3,1,1);
        layout->addWidget(grouplab,1,4,1,1);
    }
    else
    {
        layout->addWidget(timelab,1,0,1,1);
        layout->addWidget(fglab,1,1,1,1);
        layout->addWidget(repeatlab,1,2,1,1);
        layout->addWidget(fglab2,1,3,1,1);
        layout->addWidget(remindlab,1,4,1,1);
        layout->addWidget(fglab3,1,5,1,1);
        layout->addWidget(grouplab,1,6,1,1);
    }
    w->setLayout(layout);
    ui->listWidget_todolists->setItemWidget(item,w);
    mytodoitem2[indexnum2].item2=item;
    connect(checkBox,&QCheckBox::clicked, [=](){
        qDebug()<<"信号点击";
        auto i=mytodoitem2.begin();
        for(;i!=mytodoitem2.end();i++)
        {
            if(item==i->item2)
            {
                qDebug()<<i->label;
                updateitemtodb(*i,0);
                break;
            }
        }
        mytodoitem2.erase(i);
        ui->widget->setVisible(false);
        delete item;
        });
    updateitemtodb(mytodoitem2[indexnum2],1);
}

void mytodowindow::on_comboBox_currentIndexChanged(int index)
{
    if(indexnum2<mytodoitem2.size()) mytodoitem2[indexnum2].level=3-index;
    reflashall();
}


void mytodowindow::on_label_dtime_clicked()
{
    QPoint pos=ui->label_dtime->pos();
    c1->move(pos.x(),pos.y());
    c1->show();

}

void mytodowindow::on_label_remindtime_clicked()
{
    QPoint pos=ui->label_remindtime->pos();
    c2->move(pos.x(),pos.y());
    c2->show();
}

void mytodowindow::reflashdtime(QDate dtime,int repeat)
{
    mytodoitem2[indexnum2].we=dtime.dayOfWeek();
    switch (mytodoitem2[indexnum2].we)
    {
    case 1:ui->label_dtime->setText(dtime.toString("yyyy年MM月dd日 周一"));
           break;
    case 2:ui->label_dtime->setText(dtime.toString("yyyy年MM月dd日 周二"));
           break;
    case 3:ui->label_dtime->setText(dtime.toString("yyyy年MM月dd日 周三"));
           break;
    case 4:ui->label_dtime->setText(dtime.toString("yyyy年MM月dd日 周四"));
           break;
    case 5:ui->label_dtime->setText(dtime.toString("yyyy年MM月dd日 周五"));
           break;
    case 6:ui->label_dtime->setText(dtime.toString("yyyy年MM月dd日 周六"));
           break;
    case 7:ui->label_dtime->setText(dtime.toString("yyyy年MM月dd日 周日"));
           break;
    }
    mytodoitem2[indexnum2].time=dtime.toString("yyyy年MM月dd日");
    mytodoitem2[indexnum2].Repeat=repeat;
    reflashall();
}

void mytodowindow::reflashremindtime(QDate retime,QTime retimed)
{
    mytodoitem2[indexnum2].remind=retime.toString("yyyy年MM月dd日")+retimed.toString(" HH:mm")+" 提醒";
    ui->label_remindtime->setText(mytodoitem2[indexnum2].remind);
    reflashall();
}



void mytodowindow::on_textEdit_desc_textChanged()
{
    mytodoitem2[indexnum2].description=ui->textEdit_desc->document()->toPlainText();
    updateitemtodb(mytodoitem2[indexnum2],1);
}

void mytodowindow::on_textEdit_place_textChanged()
{
    mytodoitem2[indexnum2].place=ui->textEdit_place->document()->toPlainText();
    updateitemtodb(mytodoitem2[indexnum2],1);
}

void mytodowindow::on_textEdit_note_textChanged()
{
    mytodoitem2[indexnum2].note=ui->textEdit_note->document()->toPlainText();
    updateitemtodb(mytodoitem2[indexnum2],1);
}

void mytodowindow::reflashItems(todoitem &i)
{
    QListWidgetItem *item=new QListWidgetItem;
    item->setSizeHint(QSize(1100, 80));
    ui->listWidget_todolists->addItem(item);
    QWidget *w=new QWidget;
    QLabel *lab=new QLabel;
    QLabel *levellab=new QLabel;
    QLabel *timelab=new QLabel;
    QLabel *repeatlab=new QLabel;
    QLabel *remindlab=new QLabel;
    QLabel *grouplab=new QLabel;
    QLabel *fglab=new QLabel;
    QLabel *fglab2=new QLabel;
    QLabel *fglab3=new QLabel;
    timelab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    timelab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    timelab->setText(i.time);
    repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    switch(i.Repeat)
    {
    case 0:repeatlab->setText("不重复");
           break;
    case 1:repeatlab->setText("每天重复");
           break;
    case 2:repeatlab->setText("每周重复");
           break;
    case 3:repeatlab->setText("每月重复");
           break;
    }
    QPixmap pix;
    switch(i.level)
    {
    case 1:pix.load(":/image/low.png");
        break;
    case 2:pix.load(":/image/mid.png");
        break;
    case 3:pix.load(":/image/high.png");
        break;
    }
    levellab->setPixmap(pix);
    grouplab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    grouplab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    grouplab->setText(i.group);
    remindlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    remindlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    remindlab->setText(i.remind);
    fglab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab->setText("|");
    fglab2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab2->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab2->setText("|");
    fglab3->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab3->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab3->setText("|");
    lab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    lab->setText(i.label);
    QCheckBox *checkBox=new QCheckBox(w);
    QGridLayout *layout=new QGridLayout;
    layout->setSpacing(10);
    if(i.level)
    {
        layout->addWidget(checkBox,0,0,1,1);
        layout->addWidget(levellab,0,1,1,1);
        layout->addWidget(lab,0,2,1,15);
    }
    else
    {
        layout->addWidget(checkBox,0,0,1,1);
        layout->addWidget(lab,0,1,1,15);
    }
    if(i.remind=="未安排")
    {
        layout->addWidget(timelab,1,0,1,1);
        layout->addWidget(fglab,1,1,1,1);
        layout->addWidget(repeatlab,1,2,1,1);
        layout->addWidget(fglab2,1,3,1,1);
        layout->addWidget(grouplab,1,4,1,1);
    }
    else
    {
        layout->addWidget(timelab,1,0,1,1);
        layout->addWidget(fglab,1,1,1,1);
        layout->addWidget(repeatlab,1,2,1,1);
        layout->addWidget(fglab2,1,3,1,1);
        layout->addWidget(remindlab,1,4,1,1);
        layout->addWidget(fglab3,1,5,1,1);
        layout->addWidget(grouplab,1,6,1,1);
    }
    w->setLayout(layout);
    ui->listWidget_todolists->setItemWidget(item,w);
    i.item2=item;
    connect(checkBox,&QCheckBox::clicked, [=](){
        qDebug()<<"信号点击";
        auto i2=mytodoitem2.begin();
        for(;i2!=mytodoitem2.end();i2++)
        {
            if(item==i2->item2)
            {
                qDebug()<<i2->label;
                updateitemtodb(*i2,0);
                break;
            }
        }
        mytodoitem2.erase(i2);
        ui->widget->setVisible(false);
        delete item;
        });
}

void mytodowindow::on_comboBox_2_currentIndexChanged(int index)
{
    for(auto i=mytodoitem2.begin();i!=mytodoitem2.end();i++)
    {
        if(i->item2!=nullptr) delete i->item2;
    }
    switch (index)
    {
    case 0:
        for(auto i=mytodoitem2.begin();i!=mytodoitem2.end();i++)
            for(auto j=i;j!=mytodoitem2.end();j++)
            {
                QDate itime=QDate::fromString(i->time,"yyyy年MM月dd日");
                QDate jtime=QDate::fromString(j->time,"yyyy年MM月dd日");
                if(itime>jtime)
                {
                    todoitem temp=*i;
                    *i=*j;
                    *j=temp;
                }
            }
        break;
    case 1:
        for(auto i=mytodoitem2.begin();i!=mytodoitem2.end();i++)
            for(auto j=i;j!=mytodoitem2.end();j++)
            {
                if(i->createTime>j->createTime)
                {
                    todoitem temp=*i;
                    *i=*j;
                    *j=temp;
                }
            }
        break;
     case 2:
        for(auto i=mytodoitem2.begin();i!=mytodoitem2.end();i++)
            for(auto j=i;j!=mytodoitem2.end();j++)
            {
                if(i->level<j->level)
                {
                    todoitem temp=*i;
                    *i=*j;
                    *j=temp;
                }
            }
        break;
    }
    indexnum2=0;
    qDebug()<<" ";
    for(auto i=mytodoitem2.begin();i!=mytodoitem2.end();i++,indexnum2++)
    {
        QListWidgetItem *item=new QListWidgetItem;
        item->setSizeHint(QSize(1100, 80));
        ui->listWidget_todolists->addItem(item);
        QWidget *w=new QWidget;
        QLabel *lab=new QLabel;
        QLabel *levellab=new QLabel;
        QLabel *timelab=new QLabel;
        QLabel *repeatlab=new QLabel;
        QLabel *remindlab=new QLabel;
        QLabel *grouplab=new QLabel;
        QLabel *fglab=new QLabel;
        QLabel *fglab2=new QLabel;
        QLabel *fglab3=new QLabel;
        timelab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        timelab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        timelab->setText(i->time);
        repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        switch(i->Repeat)
        {
        case 0:repeatlab->setText("不重复");
               break;
        case 1:repeatlab->setText("每天重复");
               break;
        case 2:repeatlab->setText("每周重复");
               break;
        case 3:repeatlab->setText("每月重复");
               break;
        }
        QPixmap pix;
        switch(i->level)
        {
        case 1:pix.load(":/image/low.png");
            break;
        case 2:pix.load(":/image/mid.png");
            break;
        case 3:pix.load(":/image/high.png");
            break;
        }
        levellab->setPixmap(pix);
        grouplab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        grouplab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        grouplab->setText(i->group);
        remindlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        remindlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        remindlab->setText(i->remind);
        fglab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        fglab->setText("|");
        fglab2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab2->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        fglab2->setText("|");
        fglab3->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab3->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        fglab3->setText("|");
        lab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        lab->setText(i->label);
        QCheckBox *checkBox=new QCheckBox(w);
        QGridLayout *layout=new QGridLayout;
        layout->setSpacing(10);
        if(i->level)
        {
            layout->addWidget(checkBox,0,0,1,1);
            layout->addWidget(levellab,0,1,1,1);
            layout->addWidget(lab,0,2,1,15);
        }
        else
        {
            layout->addWidget(checkBox,0,0,1,1);
            layout->addWidget(lab,0,1,1,15);
        }
        if(i->remind=="未安排")
        {
            layout->addWidget(timelab,1,0,1,1);
            layout->addWidget(fglab,1,1,1,1);
            layout->addWidget(repeatlab,1,2,1,1);
            layout->addWidget(fglab2,1,3,1,1);
            layout->addWidget(grouplab,1,4,1,1);
        }
        else
        {
            layout->addWidget(timelab,1,0,1,1);
            layout->addWidget(fglab,1,1,1,1);
            layout->addWidget(repeatlab,1,2,1,1);
            layout->addWidget(fglab2,1,3,1,1);
            layout->addWidget(remindlab,1,4,1,1);
            layout->addWidget(fglab3,1,5,1,1);
            layout->addWidget(grouplab,1,6,1,1);
        }
        w->setLayout(layout);
        ui->listWidget_todolists->setItemWidget(item,w);
        i->item2=item;
        connect(checkBox,&QCheckBox::clicked, [=](){
            qDebug()<<"信号点击";
            auto i2=mytodoitem2.begin();
            for(;i2!=mytodoitem2.end();i2++)
            {
                if(item==i2->item2)
                {
                    qDebug()<<i2->label;
                    updateitemtodb(*i2,0);
                    break;
                }
            }
            mytodoitem2.erase(i2);
            ui->widget->setVisible(false);
            delete item;
            });
    }
}

void mytodowindow::on_pushButton_clicked()
{
    ui->widget->setVisible(false);
    for(auto i=mytodoitem2.begin();i!=mytodoitem2.end();i++)
    {
        if(i->item2!=nullptr) delete i->item2;
    }
    mytodoitem2.clear();
    QSqlQuery query1;
    query1.exec("select * from mtodolist3 where already=1 and groupname='我的待办';");
        while(query1.next())
        {
            todoitem newitem;
            newitem.key=query1.value(0).toInt();
            newitem.createTime=QDateTime::fromString(query1.value(1).toString(),"yyyyMMddhhmm");
            newitem.label=query1.value(2).toString();
            newitem.time=query1.value(3).toString();
            newitem.group=query1.value(4).toString();
            newitem.Repeat=query1.value(5).toInt();
            newitem.remind=query1.value(6).toString();
            newitem.place=query1.value(7).toString();
            newitem.description=query1.value(8).toString();
            newitem.note=query1.value(9).toString();
            newitem.level=query1.value(10).toInt();
            newitem.we=QDate::fromString(newitem.time,"yyyy年MM月dd日").dayOfWeek();
            qDebug()<<newitem.key<<newitem.createTime<<newitem.label<<newitem.group<<newitem.remind<<newitem.place<<newitem.description<<newitem.note<<newitem.level<<newitem.we;
            reflashItems(newitem);
            mytodoitem2.push_back(newitem);
        }
}

void mytodowindow::additemtodb(todoitem i)
{
    QSqlQuery query2;
    QString sql=QString("insert into mtodolist3(keynum,creattime,label,time,groupname,repeat,remind,place, desc,note, level, already) values (%1,'%2','%3','%4','%5',%6,'%7','%8','%9','%10',%11,%12)")
            .arg(i.key)
            .arg(i.createTime.toString("yyyyMMddhhmm"))
            .arg(i.label)
            .arg(i.time)
            .arg(i.group)
            .arg(i.Repeat)
            .arg(i.remind)
            .arg(i.place)
            .arg(i.description)
            .arg(i.note)
            .arg(i.level)
            .arg(1);
        if(query2.exec(sql))
        {
             qDebug()<<"添加成功";
        }
        else
        {
            qDebug()<<"添加失败:"<<query2.lastError().text();
        }
        query2.finish();
}

void mytodowindow::updateitemtodb(todoitem i,int q)
{
    QSqlQuery query;
        //方式一，直接执行SQL语句
        if(query.exec(QString(R"(UPDATE mtodolist3 SET time='%1', repeat=%2, remind='%3', place='%4', desc='%5',note='%6', level=%7, already=%8  WHERE keynum=%9;)")
                   .arg(i.time).arg(i.Repeat).arg(i.remind).arg(i.place).arg(i.description).arg(i.note).arg(i.level).arg(q).arg(i.key)))
            qDebug()<<"修改成功";
        query.finish();

}

void mytodowindow::on_pushButton_2_clicked(bool checked)
{
    if(checked)
    {
        ui->listWidget->setVisible(true);
        ui->pushButton_2->setText("隐藏已完成");
        addalreadyitem();
    }
    else
    {
        ui->listWidget->setVisible(false);
        ui->pushButton_2->setText("显示已完成");
        ui->widget_2->setVisible(false);
    }
}

void mytodowindow::addalreadyitem()
{
    for(auto i=alreadyitem2.begin();i!=alreadyitem2.end();i++)
    {
        if(i->item2!=nullptr) delete i->item2;
    }
    alreadyitem2.clear();
    QSqlQuery query1;
    query1.exec("select * from mtodolist3 where already=0 and groupname='我的待办';");
        while(query1.next())
        {
            todoitem newitem;
            newitem.key=query1.value(0).toInt();
            newitem.createTime=QDateTime::fromString(query1.value(1).toString(),"yyyyMMddhhmm");
            newitem.label=query1.value(2).toString();
            newitem.time=query1.value(3).toString();
            newitem.group=query1.value(4).toString();
            newitem.Repeat=query1.value(5).toInt();
            newitem.remind=query1.value(6).toString();
            newitem.place=query1.value(7).toString();
            newitem.description=query1.value(8).toString();
            newitem.note=query1.value(9).toString();
            newitem.level=query1.value(10).toInt();
            newitem.we=QDate::fromString(newitem.time,"yyyy年MM月dd日").dayOfWeek();
            qDebug()<<newitem.key<<newitem.createTime<<newitem.label<<newitem.group<<newitem.remind<<newitem.place<<newitem.description<<newitem.note<<newitem.level<<newitem.we;
            reflashalreadyitem(newitem);
            alreadyitem2.push_back(newitem);
        }
}

void mytodowindow::reflashalreadyitem(todoitem &i)
{
    QListWidgetItem *item=new QListWidgetItem;
    item->setSizeHint(QSize(1100, 80));
    ui->listWidget->addItem(item);
    QWidget *w=new QWidget;
    QLabel *lab=new QLabel;
    QLabel *levellab=new QLabel;
    QLabel *timelab=new QLabel;
    QLabel *repeatlab=new QLabel;
    QLabel *remindlab=new QLabel;
    QLabel *grouplab=new QLabel;
    QLabel *fglab=new QLabel;
    QLabel *fglab2=new QLabel;
    QLabel *fglab3=new QLabel;
    timelab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    timelab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray;text-decoration:line-through;}");
    timelab->setText(i.time);
    repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray;text-decoration:line-through;}");
    switch(i.Repeat)
    {
    case 0:repeatlab->setText("不重复");
           break;
    case 1:repeatlab->setText("每天重复");
           break;
    case 2:repeatlab->setText("每周重复");
           break;
    case 3:repeatlab->setText("每月重复");
           break;
    }
    QPixmap pix;
    switch(i.level)
    {
    case 1:pix.load(":/image/low.png");
        break;
    case 2:pix.load(":/image/mid.png");
        break;
    case 3:pix.load(":/image/high.png");
        break;
    }
    levellab->setPixmap(pix);
    grouplab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    grouplab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray;text-decoration:line-through;}");
    grouplab->setText(i.group);
    remindlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    remindlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray;text-decoration:line-through;}");
    remindlab->setText(i.remind);
    fglab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab->setText("|");
    fglab2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab2->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab2->setText("|");
    fglab3->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    fglab3->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
    fglab3->setText("|");
    lab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    lab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray;text-decoration:line-through;}");
    lab->setText(i.label);
    QGridLayout *layout=new QGridLayout;
    layout->setSpacing(10);
    if(i.level)
    {
        layout->addWidget(lab,0,0,1,15);
    }
    else
    {
        layout->addWidget(lab,0,0,1,15);
    }
    if(i.remind=="未安排")
    {
        layout->addWidget(timelab,1,0,1,1);
        layout->addWidget(fglab,1,1,1,1);
        layout->addWidget(repeatlab,1,2,1,1);
        layout->addWidget(fglab2,1,3,1,1);
        layout->addWidget(grouplab,1,4,1,1);
    }
    else
    {
        layout->addWidget(timelab,1,0,1,1);
        layout->addWidget(fglab,1,1,1,1);
        layout->addWidget(repeatlab,1,2,1,1);
        layout->addWidget(fglab2,1,3,1,1);
        layout->addWidget(remindlab,1,4,1,1);
        layout->addWidget(fglab3,1,5,1,1);
        layout->addWidget(grouplab,1,6,1,1);
    }
    w->setLayout(layout);
    ui->listWidget->setItemWidget(item,w);
    i.item2=item;
}

void mytodowindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    auto i=alreadyitem2.begin();
    bool flag=true;
    for(;i!=alreadyitem2.end();i++)
    {
        if(i->item2==item)
        {
            flag=false;
            break;
        }
    }
    if(flag) return;
    ui->widget_2->setVisible(true);
    ui->label_name_already->setText(i->label);
    QPixmap pix;
    switch(i->level)
    {
    case 0:pix.load(":/image/null.png");
           ui->label_level_already->setText("无优先级");
        break;
    case 1:pix.load(":/image/low.png");
        ui->label_level_already->setText("低");
        break;
    case 2:pix.load(":/image/mid.png");
        ui->label_level_already->setText("中");
        break;
    case 3:pix.load(":/image/high.png");
        ui->label_level_already->setText("高");
        break;
    }
    ui->label_level_already_icon->setPixmap(pix);
    ui->label_time_already->setText(i->time);
    ui->label_remind_already->setText(i->remind);
    ui->textBrowser->setText(i->description);
    ui->textBrowser_2->setText(i->place);
    ui->textBrowser_3->setText(i->note);
}
