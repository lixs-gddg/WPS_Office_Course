#include "first_window.h"
#include "ui_first_window.h"

first_window::first_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::first_window)
{
    ui->setupUi(this);
    ui->lineEdit_newtodo->setStyleSheet("color:green");
    connect(ui->lineEdit_newtodo, SIGNAL(clicked()), this, SLOT(lineEditClicked()));
    //待办栏
    QTreeWidgetItem *topItem1=new QTreeWidgetItem(ui->treeWidget_todolists);
    topItem1->setText(0,"未安排");
    items.append(topItem1);
    QTreeWidgetItem *topItem2=new QTreeWidgetItem(ui->treeWidget_todolists);
    topItem2->setText(0,"未来七天");
    items.append(topItem2);
    QTreeWidgetItem *topItem3=new QTreeWidgetItem(ui->treeWidget_todolists);
    topItem3->setText(0,"已逾期");
    items.append(topItem3);
    QTreeWidgetItem *topItem4=new QTreeWidgetItem(ui->treeWidget_todolists);
    topItem4->setText(0,"以后");
    items.append(topItem4);
    ui->widget->setVisible(false);
    c1=new mycalenderwidget(ui->widget);
    c1->hide();
    connect(c1,SIGNAL(senddtime(QDate,int)),this,SLOT(reflashdtime(QDate,int)));
    c2=new remindcalendarwidget(ui->widget);
    c2->hide();
    connect(c2,SIGNAL(sendremindtime(QDate,QTime)),this,SLOT(reflashremindtime(QDate,QTime)));
}

first_window::~first_window()
{
    delete ui;
}

void first_window::lineEditClicked() {
    ui->lineEdit_newtodo->setText("");
    ui->lineEdit_newtodo->setStyleSheet("color:black");
    ui->lineEdit_newtodo->setPlaceholderText("输入内容后，回车创建成功");
}



void first_window::on_lineEdit_newtodo_returnPressed()
{
    newtodo=ui->lineEdit_newtodo->text();
    ui->lineEdit_newtodo->setStyleSheet("color:green");
    ui->lineEdit_newtodo->setText("+ 新建待办");
    ui->treeWidget_todolists->setFocus();//让输入框失去焦点
    todoitem newitem;
    newitem.label=newtodo;
    newitem.createTime=QDateTime::currentDateTime();
    newitem.group=groupname;
    qDebug()<<indexkey;
    newitem.key=indexkey++;
    //添加新项。
    QTreeWidgetItem *item=new QTreeWidgetItem(items[0]);
    //item的widget
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
    grouplab->setText(groupname);
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
    //
    newitem.item=item;
    mytodoitem.push_back(newitem);
    ui->treeWidget_todolists->setItemWidget(item,0,w);
    connect(checkBox,&QCheckBox::clicked, [=](){
        qDebug()<<"信号点击";
        auto i=mytodoitem.begin();
        for(;i!=mytodoitem.end();i++)
        {
            if(item==i->item)
            {
                qDebug()<<i->label;
                updateitemtodb(*i,0);
                break;
            }
        }
        mytodoitem.erase(i);
        ui->widget->setVisible(false);
        delete item;
        });
    additemtodb(newitem);
}



void first_window::on_treeWidget_todolists_itemClicked(QTreeWidgetItem *item, int column)
{
    bool flag=true;
    auto i=mytodoitem.begin();
    for(indexnum=0;i!=mytodoitem.end();i++,indexnum++)
    {
        if(item==i->item)
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

void first_window::on_comboBox_currentIndexChanged(int index)
{
    if(indexnum<mytodoitem.size()) mytodoitem[indexnum].level=3-index;
    updateitemtodb(mytodoitem[indexnum],1);
    reflashall();
}

void first_window::on_label_dtime_clicked()
{
    QPoint pos=ui->label_dtime->pos();
    c1->move(pos.x(),pos.y());
    c1->show();

}

void first_window::on_label_remindtime_clicked()
{
    QPoint pos=ui->label_remindtime->pos();
    c2->move(pos.x(),pos.y());
    c2->show();
}

void first_window::on_textEdit_desc_textChanged()
{
    mytodoitem[indexnum].description=ui->textEdit_desc->document()->toPlainText();
    updateitemtodb(mytodoitem[indexnum],1);
}

void first_window::on_textEdit_place_textChanged()
{
    mytodoitem[indexnum].place=ui->textEdit_place->document()->toPlainText();
    updateitemtodb(mytodoitem[indexnum],1);
}

void first_window::on_textEdit_note_textChanged()
{
    mytodoitem[indexnum].note=ui->textEdit_note->document()->toPlainText();
    updateitemtodb(mytodoitem[indexnum],1);
}

void first_window::reflashdtime(QDate dtime,int repeat)
{
    mytodoitem[indexnum].we=dtime.dayOfWeek();
    switch (mytodoitem[indexnum].we)
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
    mytodoitem[indexnum].time=dtime.toString("yyyy年MM月dd日");
    mytodoitem[indexnum].Repeat=repeat;
    reflashall();
}

void first_window::reflashremindtime(QDate retime,QTime retimed)
{
    mytodoitem[indexnum].remind=retime.toString("yyyy年MM月dd日")+retimed.toString(" HH:mm ")+"提醒";
    ui->label_remindtime->setText(mytodoitem[indexnum].remind);
    reflashall();
}

void first_window::reflashall()
{
    delete mytodoitem[indexnum].item;
    if(mytodoitem[indexnum].time=="未安排")
    {
        QTreeWidgetItem *newitem=new QTreeWidgetItem(items[0]);
        //item的widget
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
        timelab->setText(mytodoitem[indexnum].time);
        repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        switch(mytodoitem[indexnum].Repeat)
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
        switch(mytodoitem[indexnum].level)
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
        grouplab->setText(mytodoitem[indexnum].group);
        remindlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        remindlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        remindlab->setText(mytodoitem[indexnum].remind);
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
        lab->setText(mytodoitem[indexnum].label);
        QCheckBox *checkBox=new QCheckBox(w);
        QGridLayout *layout=new QGridLayout;
        layout->setSpacing(10);
        if(mytodoitem[indexnum].level)
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
        if(mytodoitem[indexnum].remind=="未安排")
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
        mytodoitem[indexnum].item=newitem;
        ui->treeWidget_todolists->setItemWidget(newitem,0,w);
        connect(checkBox,&QCheckBox::clicked, [=](){
            qDebug()<<"信号点击";
            auto i=mytodoitem.begin();
            for(;i!=mytodoitem.end();i++)
            {
                if(newitem==i->item)
                {
                    qDebug()<<i->label;
                    updateitemtodb(*i,0);
                    break;
                }
            }
            mytodoitem.erase(i);
            ui->widget->setVisible(false);
            delete newitem;
            });
        return;
    }
    QDate dtime;
    dtime=dtime.fromString( mytodoitem[indexnum].time,"yyyy年MM月dd日");
    QDate curdate=QDate::currentDate();
    int datenum=curdate.daysTo(dtime);
    if(datenum<0)
    {
        QTreeWidgetItem *newitem=new QTreeWidgetItem(items[2]);
        //item的widget
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
        timelab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        timelab->setText(mytodoitem[indexnum].time);
        repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        switch(mytodoitem[indexnum].Repeat)
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
        switch(mytodoitem[indexnum].level)
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
        grouplab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        grouplab->setText(mytodoitem[indexnum].group);
        remindlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        remindlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        remindlab->setText(mytodoitem[indexnum].remind);
        fglab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        fglab->setText("|");
        fglab2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab2->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        fglab2->setText("|");
        fglab3->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab3->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        fglab3->setText("|");
        lab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab3->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        lab->setText(mytodoitem[indexnum].label);
        QCheckBox *checkBox=new QCheckBox(w);
        QGridLayout *layout=new QGridLayout;
        layout->setSpacing(10);
        if(mytodoitem[indexnum].level)
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
        if(mytodoitem[indexnum].remind=="未安排")
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
        mytodoitem[indexnum].item=newitem;
        ui->treeWidget_todolists->setItemWidget(newitem,0,w);
        connect(checkBox,&QCheckBox::clicked, [=](){
            qDebug()<<"信号点击";
            auto i=mytodoitem.begin();
            for(;i!=mytodoitem.end();i++)
            {
                if(newitem==i->item)
                {
                    qDebug()<<i->label;
                    updateitemtodb(*i,0);
                    break;
                }
            }
            mytodoitem.erase(i);
            ui->widget->setVisible(false);
            delete newitem;
            });
    }
    else if(datenum<=7)
    {
        QTreeWidgetItem *newitem=new QTreeWidgetItem(items[1]);
        //item的widget
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
        timelab->setText(mytodoitem[indexnum].time);
        repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        switch(mytodoitem[indexnum].Repeat)
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
        switch(mytodoitem[indexnum].level)
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
        grouplab->setText(mytodoitem[indexnum].group);
        remindlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        remindlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        remindlab->setText(mytodoitem[indexnum].remind);
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
        lab->setText(mytodoitem[indexnum].label);
        QCheckBox *checkBox=new QCheckBox(w);
        QGridLayout *layout=new QGridLayout;
        layout->setSpacing(10);
        if(mytodoitem[indexnum].level)
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
        if(mytodoitem[indexnum].remind=="未安排")
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
        mytodoitem[indexnum].item=newitem;
        ui->treeWidget_todolists->setItemWidget(newitem,0,w);
        connect(checkBox,&QCheckBox::clicked, [=](){
            qDebug()<<"信号点击";
            auto i=mytodoitem.begin();
            for(;i!=mytodoitem.end();i++)
            {
                if(newitem==i->item)
                {
                    qDebug()<<i->label;
                    updateitemtodb(*i,0);
                    break;
                }
            }
            mytodoitem.erase(i);
            ui->widget->setVisible(false);
            delete newitem;
            });
    }
    else
    {
        QTreeWidgetItem *newitem=new QTreeWidgetItem(items[3]);
        //item的widget
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
        timelab->setText(mytodoitem[indexnum].time);
        repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        switch(mytodoitem[indexnum].Repeat)
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
        switch(mytodoitem[indexnum].level)
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
        grouplab->setText(mytodoitem[indexnum].group);
        remindlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        remindlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:gray}");
        remindlab->setText(mytodoitem[indexnum].remind);
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
        lab->setText(mytodoitem[indexnum].label);
        QCheckBox *checkBox=new QCheckBox(w);
        QGridLayout *layout=new QGridLayout;
        layout->setSpacing(10);
        if(mytodoitem[indexnum].level)
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
        if(mytodoitem[indexnum].remind=="未安排")
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
        mytodoitem[indexnum].item=newitem;
        ui->treeWidget_todolists->setItemWidget(newitem,0,w);
        connect(checkBox,&QCheckBox::clicked, [=](){
            qDebug()<<"信号点击";
            auto i=mytodoitem.begin();
            for(;i!=mytodoitem.end();i++)
            {
                if(newitem==i->item)
                {
                    qDebug()<<i->label;
                    updateitemtodb(*i,0);
                    break;
                }
            }
            mytodoitem.erase(i);
            ui->widget->setVisible(false);
            delete newitem;
            });
    }
    updateitemtodb(mytodoitem[indexnum],1);
}


void first_window::reflashItems(todoitem &i)
{
    if(i.time=="未安排")
    {
        QTreeWidgetItem *newitem=new QTreeWidgetItem(items[0]);
        //item的widget
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
        i.item=newitem;
        ui->treeWidget_todolists->setItemWidget(newitem,0,w);
        connect(checkBox,&QCheckBox::clicked, [=](){
            qDebug()<<"信号点击";
            auto i=mytodoitem.begin();
            for(;i!=mytodoitem.end();i++)
            {
                if(newitem==i->item)
                {
                    qDebug()<<i->label;
                    updateitemtodb(*i,0);
                    break;
                }
            }
            mytodoitem.erase(i);
            ui->widget->setVisible(false);
            delete newitem;
            });
        return;
    }
    QDate dtime;
    dtime=dtime.fromString( i.time,"yyyy年MM月dd日");
    QDate curdate=QDate::currentDate();
    int datenum=curdate.daysTo(dtime);
    if(datenum<0)
    {
        QTreeWidgetItem *newitem=new QTreeWidgetItem(items[2]);
        //item的widget
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
        timelab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        timelab->setText(i.time);
        repeatlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        repeatlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
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
        grouplab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        grouplab->setText(i.group);
        remindlab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        remindlab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        remindlab->setText(i.remind);
        fglab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        fglab->setText("|");
        fglab2->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab2->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        fglab2->setText("|");
        fglab3->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab3->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
        fglab3->setText("|");
        lab->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        fglab3->setStyleSheet("QLabel{font-size:15px;font-weight:15px;color:red}");
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
       i.item=newitem;
        ui->treeWidget_todolists->setItemWidget(newitem,0,w);
        connect(checkBox,&QCheckBox::clicked, [=](){
            qDebug()<<"信号点击";
            auto i=mytodoitem.begin();
            for(;i!=mytodoitem.end();i++)
            {
                if(newitem==i->item)
                {
                    qDebug()<<i->label;
                    updateitemtodb(*i,0);
                    break;
                }
            }
            mytodoitem.erase(i);
            ui->widget->setVisible(false);
            delete newitem;
            });
    }
    else if(datenum<=7)
    {
        QTreeWidgetItem *newitem=new QTreeWidgetItem(items[1]);
        //item的widget
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
        i.item=newitem;
        ui->treeWidget_todolists->setItemWidget(newitem,0,w);
        connect(checkBox,&QCheckBox::clicked, [=](){
            qDebug()<<"信号点击";
            auto i=mytodoitem.begin();
            for(;i!=mytodoitem.end();i++)
            {
                if(newitem==i->item)
                {
                    qDebug()<<i->label;
                    updateitemtodb(*i,0);
                    break;
                }
            }
            mytodoitem.erase(i);
            ui->widget->setVisible(false);
            delete newitem;
            });
    }
    else
    {
        QTreeWidgetItem *newitem=new QTreeWidgetItem(items[3]);
        //item的widget
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
        i.item=newitem;
        ui->treeWidget_todolists->setItemWidget(newitem,0,w);
        connect(checkBox,&QCheckBox::clicked, [=](){
            qDebug()<<"信号点击";
            auto i=mytodoitem.begin();
            for(;i!=mytodoitem.end();i++)
            {
                if(newitem==i->item)
                {
                    qDebug()<<i->label;
                    updateitemtodb(*i,0);
                    break;
                }
            }
            mytodoitem.erase(i);
            ui->widget->setVisible(false);
            delete newitem;
            });
    }
}

void first_window::on_pushButton_clicked()
{
    ui->widget->setVisible(false);
    for(auto i=mytodoitem.begin();i!=mytodoitem.end();i++)
    {
        if(i->item!=nullptr) delete i->item;
    }
    mytodoitem.clear();
    QSqlQuery query1;
    query1.exec("select * from mtodolist3 where already=1;");
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
            mytodoitem.push_back(newitem);
        }
}
void first_window::additemtodb(todoitem i)
{
    QSqlQuery query1;
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
        if(query1.exec(sql))
        {
             qDebug()<<"添加成功";
        }
        else
        {
            qDebug()<<"添加失败:"<<query1.lastError().text();
        }
        query1.finish();
}

void first_window::updateitemtodb(todoitem i,int q)
{
    QSqlQuery query;
        //方式一，直接执行SQL语句
    if(query.exec(QString(R"(UPDATE mtodolist3 SET time='%1', repeat=%2, remind='%3', place='%4', desc='%5',note='%6', level=%7, already=%8  WHERE keynum=%9;)")
               .arg(i.time).arg(i.Repeat).arg(i.remind).arg(i.place).arg(i.description).arg(i.note).arg(i.level).arg(q).arg(i.key)))
        qDebug()<<"修改成功";
        query.finish();
}

