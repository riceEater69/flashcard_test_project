#pragma once
#include "card.h"
#include <QDebug>
#include "ui_card.h"
#include <iostream>
#include <fstream>
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



    std::ifstream incolor;
    incolor.open("color");
    if(incolor.good()){

        std::string line;

        while(std::getline(incolor,line))
        {
            card_styles.push_back(line);
        }

        incolor.close();
    }
    else
    {




        card_styles.push_back("Times New Roman,11,-1,5,700,1,0,0,0,0,0,0,0,0,0,1,Bold Italic");
        card_styles.push_back("#000000");
        card_styles.push_back("#ffffff");
        card_styles.push_back("#ffffff");
        update_styles_to_file();


    }
    //seting defalt(current) color/styles
    setfontcolor();
    setcolorforbg2();
    setcolor_for_card_elements();
    setcolor_for_card_bg();

    index = 0;

    // Copy cardlist directly instead of using pointers
    card_list = *cardlist;

    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector using std::shuffle
    std::shuffle(card_list.begin(), card_list.end(), g);

    // Update label with the first question
//    ui->label_2->setText(QString("Question:\n%1").arg(QString::fromStdString(card_list[index].question)));
    newQuestion();

    // Set label for answer


    // Connect button clicks to slots
//    connect(ui->pushButton_2, &QPushButton::clicked, this, &card::on_pushButton_2_clicked);
//    connect(ui->pushButton, &QPushButton::clicked, this, &card::on_pushButton_clicked);
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
//        ui->pause->setText("unpause");
      }
      else{
        pauser=false;
                  clock.start(1000);
//         ui->pause->setText("pause");
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

        card_styles[0]=font.toString().toStdString();
        setfontcolor();
        update_styles_to_file();




      }else return;
}


void card::setfontcolor(){
        //ui->start->setFont(QFont(QString::fromStdString(card_styles[0])));
      //ui->pause->setFont(QFont(QString::fromStdString(card_styles[0])));

      //ui->stop->setFont(QFont(card_styles[0]));
      ui->pushButton_2->setFont(QFont(QString::fromStdString(card_styles[0])));
      ui->pushButton_3->setFont(QFont(QString::fromStdString(card_styles[0])));

      ui->pushButton->setFont(QFont(QString::fromStdString(card_styles[0])));
      ui->label_2->setFont(QFont(QString::fromStdString(card_styles[0])));
      ui->label->setFont(QFont(QString::fromStdString(card_styles[0])));

      ui->seconds->setFont(QFont(QString::fromStdString(card_styles[0])));
      ui->minutes->setFont(QFont(QString::fromStdString(card_styles[0])));

}

// Assuming you have a QPushButton named 'yourButton' in your UI


void card::on_textcolor_clicked()
{
      // Get the selected text color using QColorDialog
      QColor textColor = QColorDialog::getColor(Qt::black, this, "Select Text Color");

      // If the user selected a color, update the text color for relevant components
      if (textColor.isValid()) {
                card_styles[1]=textColor.name().toStdString();
                setcolor_for_card_elements();
                update_styles_to_file();

      }
}

void card::update_styles_to_file(){
      std::ofstream ofile;
      ofile.open("color");//open blank file for writing
      ofile << card_styles[0]<<std::endl<<card_styles[1]<<std::endl<<card_styles[2]<<std::endl<<card_styles[3];
      ofile.close();
}
void card:: setcolor_for_card_elements()
{
      ui->label_2->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
      ui->label->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
      ui->minutes->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
      ui->seconds->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
      //                ui->start->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
      //                ui->pause->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
      //                ui->stop->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
      ui->pushButton_2->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
      ui->pushButton_3->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
      ui->pushButton->setStyleSheet(QString("color: %1;").arg(QString::fromStdString(card_styles[1])));
}



void card::on_background_color_clicked()

      {
                // Get the selected background color using QColorDialog
                QColor bgColor = QColorDialog::getColor(Qt::white, this, "Select Background Color");

                // If the user selected a color, update the background color for relevant components
                if (bgColor.isValid()) {
                card_styles[2]=bgColor.name().toStdString();
                setcolor_for_card_bg();
             update_styles_to_file();

      }
      }
      void card::setcolor_for_card_bg()
      {

      // Set background color for QLineEdit and QTextEdit using style sheets
      ui->groupBox->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));
      ui->label_2->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));

      // Set background color for QListWidget using style sheets

      ui->label->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));
      ui->minutes->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));
      ui->seconds->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));
      // ui->start->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));



      // ui->pause->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));
      //ui->stop->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));
      ui->pushButton_3->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));
      ui->pushButton_2->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));


      ui->pushButton->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));



      //ui->stackedWidget->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[2])));

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
                            card_styles[3]=bgColor.name().toStdString();
                            setcolorforbg2();
                            update_styles_to_file();
                        }
                    }

      }
}
void card::setcolorforbg2(){
      this->setStyleSheet(QString("background-color: %1;").arg(QString::fromStdString(card_styles[3])));
}
