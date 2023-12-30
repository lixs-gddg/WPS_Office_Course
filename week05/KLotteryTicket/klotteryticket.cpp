#include "klotteryticket.h"
#include "ui_klotteryticket.h"

KLotteryTicket::KLotteryTicket(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::KLotteryTicket)
{
    ui->setupUi(this);
}

KLotteryTicket::~KLotteryTicket()
{
    delete ui;
}

void KLotteryTicket::on_pushButton0_clicked()
{
    if(m_showInputNums.size()==1 && m_showInputNums[0]<'4'){
            m_showInputNums = m_showInputNums+'0';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton1_clicked()
{
    if(m_showInputNums.size()<2 && m_showInputNums[0]<'4'){
            m_showInputNums = m_showInputNums+'1';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton2_clicked()
{
    if(m_showInputNums.size()<2 && m_showInputNums[0]<'4'){
            m_showInputNums = m_showInputNums+'2';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton3_clicked()
{
    if(m_showInputNums.size()<2 && m_showInputNums[0]<'4'){
            m_showInputNums = m_showInputNums+'3';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton4_clicked()
{
    if(m_showInputNums.size()<2 && m_showInputNums[0]<'4'){
            m_showInputNums = m_showInputNums+'4';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton5_clicked()
{
    if(m_showInputNums.size()<2 && m_showInputNums[0]<'4'){
            m_showInputNums = m_showInputNums+'5';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton6_clicked()
{
    if(m_showInputNums.size()<2 && m_showInputNums[0]<'3'){
            m_showInputNums = m_showInputNums+'6';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton7_clicked()
{
    if(m_showInputNums.size()<2 && m_showInputNums[0]<'3'){
            m_showInputNums = m_showInputNums+'7';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton8_clicked()
{
    if(m_showInputNums.size()<2 && m_showInputNums[0]<'3'){
            m_showInputNums = m_showInputNums+'8';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton9_clicked()
{
    if(m_showInputNums.size()<2 && m_showInputNums[0]<'3'){
            m_showInputNums = m_showInputNums+'9';
            ui->textBrowser_InputNum->setText(m_showInputNums);
        }
}

void KLotteryTicket::on_pushButton_OK_clicked()
{
    if(m_showInputNums.size()==0) return;
    if(m_chosenNums.size()<7)
    {
        int num=m_showInputNums.toInt();
        bool flag=true;
        for(int i=0;i<m_chosenNums.size();i++)
        {
            if(num==m_chosenNums[i])
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            m_chosenNums.push_back(num);
            m_showChosenNums=m_showChosenNums+m_showInputNums+" ";
        }
    }
    m_showInputNums.clear();
    ui->textBrowser_InputNum->setText(m_showInputNums);
    ui->textBrowser_ChosenNums->setText(m_showChosenNums);
}

void KLotteryTicket::on_pushButton_clear_clicked()
{
    if(m_showInputNums.size()>0)
    {
        m_showInputNums.clear();
    }
    ui->textBrowser_InputNum->setText(m_showInputNums);
}

void KLotteryTicket::on_pushButton_clearall_clicked()
{
    if(m_chosenNums.size()>0)
    {
        m_chosenNums.clear();
        m_showChosenNums.clear();
    }
    ui->textBrowser_ChosenNums->setText(m_showChosenNums);
}

void KLotteryTicket::on_pushButton_start_clicked()
{
    m_showPrizeNums.clear();
    m_prizeNums.clear();
    ui->textBrowser_PrizeNums->setText(m_showPrizeNums);
    ui->textBrowser_Money->setText("");
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    if(m_chosenNums.size()==7)
    {
       for(int i=0;i<7;)
       {
           int prizenum = qrand()%35+1;
           if(m_prizeNums.indexOf(prizenum,0)==-1)
           {
               m_prizeNums.push_back(prizenum);
               m_showPrizeNums = m_showPrizeNums+ QString("%1").arg(prizenum)+" ";
               i++;
           }
       }
       ui->textBrowser_PrizeNums->setText(m_showPrizeNums);
       int count=0;
       for(int i=0;i<7;i++)
       {
           for(int j=0;j<7;j++)
           {
               if(m_chosenNums[i]==m_prizeNums[j])
               {
                   count++;
                   break;
               }
           }
       }
       switch(count)
       {
       case 0:m_money="谢谢参与！";
              break;
       case 1:m_money="5";
              break;
       case 2:m_money="50";
              break;
       case 3:m_money="100";
              break;
       case 4:m_money="500";
              break;
       case 5:m_money="10W";
              break;
       case 6:m_money="30W";
              break;
       case 7:m_money="500W";
              break;
       }
       ui->textBrowser_Money->setText(m_money);
    }
}

void KLotteryTicket::on_pushButton_Reset_clicked()
{
    m_showInputNums.clear();
    m_showPrizeNums.clear();
    m_showChosenNums.clear();
    m_money.clear();
    m_chosenNums.clear();
    m_prizeNums.clear();
    ui->textBrowser_Money->setText(m_money);
    ui->textBrowser_InputNum->setText(m_showInputNums);
    ui->textBrowser_PrizeNums->setText(m_showPrizeNums);
    ui->textBrowser_ChosenNums->setText(m_showChosenNums);
}

void KLotteryTicket::on_pushButton_exit_clicked()
{
    close();
}
