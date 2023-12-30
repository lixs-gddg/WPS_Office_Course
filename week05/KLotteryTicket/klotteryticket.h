#ifndef KLOTTERYTICKET_H
#define KLOTTERYTICKET_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVector>
#include <QtGlobal>
#include <QTime>
QT_BEGIN_NAMESPACE
namespace Ui { class KLotteryTicket; }
QT_END_NAMESPACE

class KLotteryTicket : public QWidget
{
    Q_OBJECT

public:
    KLotteryTicket(QWidget *parent = nullptr);
    ~KLotteryTicket();

private slots:
    void on_pushButton0_clicked();

    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_pushButton5_clicked();

    void on_pushButton6_clicked();

    void on_pushButton7_clicked();

    void on_pushButton8_clicked();

    void on_pushButton9_clicked();

    void on_pushButton_OK_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_clearall_clicked();

    void on_pushButton_start_clicked();

    void on_pushButton_Reset_clicked();

    void on_pushButton_exit_clicked();

private:
    Ui::KLotteryTicket *ui;
    QString m_showInputNums;
    QString m_showChosenNums;
    QString m_showPrizeNums;
    QString m_money;
    QVector<int> m_chosenNums;
    QVector<int> m_prizeNums;
};
#endif // KLOTTERYTICKET_H
