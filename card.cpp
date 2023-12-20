#pragma once
#include "card.h"
#include <QDebug>
#include "ui_card.h"
#include <iostream>
#include <vector>
#include "qna.cpp"
#include <algorithm>
#include <random>
#include<QFontDialog>
#include <QColorDialog>
#include<QColor>

card::card(std::vector <qna> *cardlist, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::card)
{
    if (cardlist->empty()) {
        // Handle the case where the card list is empty
        return;
    }

    ui->setupUi(this);


    connect(ui->textcolor, &QPushButton::clicked, this, &card::on_textcolor_clicked);
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


void card::on_font_clicked()
{
      bool ok;
      QFont font =QFontDialog::getFont(&ok,this);
      if(ok){
        ui->start->setFont(font);
        ui->pause->setFont(font);

        ui->stop->setFont(font);
        ui->pushButton_2->setFont(font);
        ui->pushButton_3->setFont(font);

        ui->pushButton->setFont(font);
        ui->label_2->setFont(font);
        ui->label->setFont(font);

        ui->seconds->setFont(font);
                ui->minutes->setFont(font);



      }else return;
}


// Assuming you have a QPushButton named 'yourButton' in your UI


void card::on_textcolor_clicked()
{
      // Get the selected text color using QColorDialog
      QColor textColor = QColorDialog::getColor(Qt::black, this, "Select Text Color");

      // If the user selected a color, update the text color for relevant components
      if (textColor.isValid()) {
                ui->label_2->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                ui->label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                ui->minutes->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                ui->seconds->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                ui->start->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                ui->pause->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                ui->stop->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                ui->pushButton_2->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                ui->pushButton_3->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                ui->pushButton->setStyleSheet(QString("color: %1;").arg(textColor.name()));
      }
}




void card::on_background_color_clicked()

      {
                // Get the selected background color using QColorDialog
                QColor bgColor = QColorDialog::getColor(Qt::white, this, "Select Background Color");

                // If the user selected a color, update the background color for relevant components
                if (bgColor.isValid()) {
                    // Set background color for QLineEdit and QTextEdit using style sheets
                    ui->groupBox->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
                    ui->label_2->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));

                    // Set background color for QListWidget using style sheets

                    ui->label->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
                    ui->minutes->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
                    ui->seconds->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
                    ui->start->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));



                    ui->pause->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
                    ui->stop->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
                    ui->pushButton_3->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
                    ui->pushButton_2->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));


                    ui->pushButton->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));



                    //ui->stackedWidget->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));

      }
      }

void card::on_background_color2_clicked()
{
      {

                    {
                        // Get the selected background color using QColorDialog
                        QColor bgColor = QColorDialog::getColor(Qt::white, this, "Select Background Color");

                        // If the user selected a color, update the background color for the main window
                        if (bgColor.isValid()) {
                            // Set background color for the main window using style sheets
                            this->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
                        }
                    }

      }
}

