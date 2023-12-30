#ifndef REMINDCALENDARWIDGET_H
#define REMINDCALENDARWIDGET_H

#include <QWidget>
#include<QDate>
#include<QTime>
namespace Ui {
class remindcalendarwidget;
}

class remindcalendarwidget : public QWidget
{
    Q_OBJECT

public:
    explicit remindcalendarwidget(QWidget *parent = nullptr);
    ~remindcalendarwidget();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_timeEdit_userTimeChanged(const QTime &time);
    void on_pushButton_no_clicked();

    void on_pushButton_yes_clicked();

signals:
    void  sendremindtime(QDate retime,QTime retimed);
private:
    Ui::remindcalendarwidget *ui;
    QDate curdate;
    QTime curtime;
};

#endif // REMINDCALENDARWIDGET_H
