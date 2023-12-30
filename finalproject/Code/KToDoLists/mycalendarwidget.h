#ifndef MYCALENDERWIDGET_H
#define MYCALENDERWIDGET_H

#include <QWidget>
#include <QDate>
namespace Ui {
class mycalenderwidget;
}

class mycalenderwidget : public QWidget
{
    Q_OBJECT

public:
    explicit mycalenderwidget(QWidget *parent = nullptr);
    ~mycalenderwidget();
signals:
    void  senddtime(QDate dtime,int repeat);

private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_no_clicked();

    void on_pushButton_yes_clicked();

private:
    Ui::mycalenderwidget *ui;
    QDate curdate;
    int currepeat=0;
};

#endif // MYCALENDERWIDGET_H
