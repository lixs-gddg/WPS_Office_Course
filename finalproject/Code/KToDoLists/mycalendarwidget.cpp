#include "mycalendarwidget.h"
#include "ui_mycalendarwidget.h"

mycalenderwidget::mycalenderwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mycalenderwidget)
{
    ui->setupUi(this);
}

mycalenderwidget::~mycalenderwidget()
{
    delete ui;
}

void mycalenderwidget::on_calendarWidget_clicked(const QDate &date)
{
    curdate=date;
}

void mycalenderwidget::on_comboBox_currentIndexChanged(int index)
{
    currepeat=index;
}

void mycalenderwidget::on_pushButton_no_clicked()
{
    this->close();
}

void mycalenderwidget::on_pushButton_yes_clicked()
{
    emit senddtime(curdate,currepeat);
    this->close();
}
