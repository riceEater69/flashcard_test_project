#pragma once
#include "card.h"
#include <QDebug>
#include "ui_card.h"
#include <iostream>
#include <vector>
#include "qna.cpp"
#include <algorithm>
#include <random>

card::card(std::vector <qna> *cardlist, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::card)
{
    if (cardlist->empty()) {
        // Handle the case where the card list is empty
        return;
    }

    ui->setupUi(this);
    second =0;
    minute=0;
    pauser= false;
    connect(&clock,SIGNAL (timeout()),this,SLOT(processor()));





    index = 0;

    // Copy cardlist directly instead of using pointers
    card_list = *cardlist;

    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector using std::shuffle
    std::shuffle(card_list.begin(), card_list.end(), g);

    // Update label with the first question
    ui->label_2->setText(QString("Question:\n%1").arg(QString::fromStdString(card_list[index].question)));
    newQuestion();

    // Set label for answer
    ui->label->setText(QString("Answer:\n"));

    // Connect button clicks to slots
    connect(ui->pushButton_2, &QPushButton::clicked, this, &card::on_pushButton_2_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &card::on_pushButton_clicked);
}


void card::setQuestionText(const QString &text)
{
    ui->label_2->setText(text);
}

void card::setAnswerText(const QString &text)
{
    ui->label->setText(text);
}

card::~card()
{
    delete ui;
}
void card::newQuestion(){

      setQuestionText(QString("Question:\n%1").arg(QString::fromStdString(card_list[index].question)));
       setAnswerText(QString("Answer:"));

}

void card::on_pushButton_2_clicked()
{
    if(index==0){
        return;
    }
    index-=1;
    //back Button
    newQuestion();


}

void card::on_pushButton_clicked()
{
   //next answer
    if(card_list.size()==index+1){
        return;
    }
    index+=1;
    newQuestion();
}

void card::on_pushButton_3_clicked()
{
      setAnswerText(QString("Answer:\n%1").arg(QString::fromStdString(card_list[index].answer)));
}


void card::on_start_clicked()
{
      clock.start(1000);
}


void card::on_pause_clicked()
{
      if (pauser==false)
      {
        clock.stop();
        pauser= true;
        ui->pause->setText("unpause");
      }
      else{
        pauser=false;
                  clock.start(1000);
         ui->pause->setText("pause");
      }

}


void card::on_stop_clicked()
{
      minute=0;
          second=0;
      pauser=false;
          ui->minutes->display(minute);
      ui->seconds->display(second);
          clock.stop();



}

void card::processor()
{
          ++second;//second++
      if(second==60)
      {
        second=0;
        minute=minute+1;
      }
      else{
        ui->seconds->display(second);
        ui->minutes->display(minute);
      }
}

