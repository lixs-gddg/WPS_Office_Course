#include "remindcalendarwidget.h"
#include "ui_remindcalendarwidget.h"

remindcalendarwidget::remindcalendarwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::remindcalendarwidget)
{
    ui->setupUi(this);
}

remindcalendarwidget::~remindcalendarwidget()
{
    delete ui;
}

void remindcalendarwidget::on_calendarWidget_clicked(const QDate &date)
{
    curdate=date;
}

void remindcalendarwidget::on_timeEdit_userTimeChanged(const QTime &time)
{
    curtime=time;
}

void remindcalendarwidget::on_pushButton_no_clicked()
{
    this->close();
}

void remindcalendarwidget::on_pushButton_yes_clicked()
{
    emit sendremindtime(curdate,curtime);
    this->close();
}
