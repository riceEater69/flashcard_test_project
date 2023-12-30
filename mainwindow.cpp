#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"card.h"
#include<QDebug>
#include<QDateTime>
#include<QMessageBox>
#include<QFont>
#include<QFontDialog>
#include <QColorDialog>
#include<QColor>
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include <iostream>
#include "qna.cpp"
#include <fstream>
#include <filesystem>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Flash_card)
{
    ui->setupUi(this);
    std::filesystem::path directoryPath = "flashcards";

    try {
        // Iterate over the files in the directory


        for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
            // Print the filename
            topics.push_back(entry.path().filename().string());// add topic to array
            //Topic ko UI
            QFrame * fm=new QFrame;
            QHBoxLayout *horizontalLayout = new QHBoxLayout(fm);
            QPushButton * btn1=new QPushButton(QString::fromStdString(entry.path().filename().string()));
            horizontalLayout->addWidget(btn1);
            QPushButton * btn2=new QPushButton(QString("delete"));
            horizontalLayout->addWidget(btn2);
            ui->verticalLayout_5->addWidget(fm);
            //dynamic ui
            std::string curtopic=entry.path().filename().string();

            connect(btn1, &QPushButton::clicked, this, [=]() {
                // Your custom slot logic with parameters here
                goTopic(curtopic);
            });
            ui->new_topic->clear();
            connect(btn2, &QPushButton::clicked, this, [=]() {
                // Your custom slot logic with parameters here
                deleteTopic(curtopic,fm);
            });

        }
    } catch (const std::filesystem::filesystem_error& e) {
        // Handle any potential filesystem errors
        std::cerr << "Error: " << e.what() << std::endl;
    }


    ui->stackedWidget->setCurrentIndex(1);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timefunction()));
    timer->start(1000);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timefunction()
{
QTime time=QTime::currentTime();
    QString time_text=time.toString("hh: mm: ss");
    if((time.second()%2) ==0)
    {
        time_text [2] =' ';
        time_text [6] =' ';

    }
    ui->label_date_time->setText(time_text);
}

void MainWindow::addTextToList() {
    QString question = ui->tquestion_text->text();
    QString answer = ui->tanswer_text->toPlainText();
    qna qs;

    qs.question=question.toStdString();
    qs.answer=answer.toStdString();

    if (!question.isEmpty() && !answer.isEmpty()) {
         this->questions.push_back(qs);


         QString displayText=QString("Question: %1").arg(question);
        ui->card_list->addItem(displayText);
        ui->tquestion_text->clear();
        ui->tanswer_text->clear();
        update_cards();
    }
}
void MainWindow::on_pushButton_8_clicked()
{






        card card(&(this->questions));






        // Set the window title and display the card
        card.setWindowTitle("cards");
        card.setModal(true);
        card.exec();




}
// MainWindow.cpp
// mainwindow.cpp

//void MainWindow::updateQuestionsAndAnswers() {
//    // Get the selected item from the list widget
//    QListWidgetItem* selectedItem = ui->card_list->currentItem();

//    if (selectedItem) {
//        // Get the text from the selected item
//        QString selectedText = selectedItem->text();

//        // Parse the text to extract question and answer
//        QStringList textParts = selectedText.split("\n");
//        if (textParts.size() == 2) {
//            QString question = textParts[0].mid(10); // Assuming "Question: " is the prefix
//            QString answer = textParts[1].mid(8);    // Assuming "Answer: " is the prefix

//            // Display question and answer in separate files or any desired way
//            // You can write to separate files or use any other method based on your requirement
//            // Example: Write to files "question.txt" and "answer.txt"
//            QFile questionFile("question.txt");
//            QFile answerFile("answer.txt");

//            if (questionFile.open(QIODevice::WriteOnly | QIODevice::Text) &&
//                answerFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
//                QTextStream questionStream(&questionFile);
//                QTextStream answerStream(&answerFile);

//                questionStream << question;
//                answerStream << answer;

//                questionFile.close();
//                answerFile.close();
//            }
//        }
//    }
//}





void MainWindow::on_add_text_clicked()
{
    addTextToList();
}

void MainWindow::on_card_list_itemSelectionChanged() {
    int currentIndex=ui->card_list->currentIndex().row();
    QListWidgetItem* selectedItem = ui->card_list->currentItem();
    if (selectedItem) {


        ui->tquestion_text->setText(QString::fromStdString(questions[currentIndex].question));
            ui->tanswer_text->setPlainText(QString::fromStdString(questions[currentIndex].answer));

    }
//    connect(ui->card_list, &QListWidget::itemSelectionChanged, this, &MainWindow::on_card_list_itemSelectionChanged);

}




void MainWindow::on_update_text_clicked()
{

        // Get the selected item
    int currentIndex=ui->card_list->currentIndex().row();
       QListWidgetItem* selectedItem = ui->card_list->currentItem();

        if (selectedItem) {

       questions[currentIndex].answer=ui->tanswer_text->toPlainText().toStdString();
        questions[currentIndex].question=ui->tquestion_text->text().toStdString();
            // Update the selected item with new text


        selectedItem->setText(QString("Question: %1")
                                  .arg(ui->tquestion_text->text()));

            update_cards();
        }


}


void MainWindow::on_remove_text_clicked()
{

            // Get the selected item
        int currentIndex=ui->card_list->currentIndex().row();

        questions.erase(questions.begin() + currentIndex);
            QListWidgetItem* selectedItem = ui->card_list->currentItem();

            if (selectedItem) {
            // Remove the selected item from the QListWidget
            delete ui->card_list->takeItem(ui->card_list->row(selectedItem));
            update_cards();
            }


}


void MainWindow::on_clear_text_clicked()
{

            // Clear the text in QLineEdit and QTextEdit
            ui->tquestion_text->clear();
            ui->tanswer_text->clear();


}


void MainWindow::on_actionFont_triggered()
{
            bool ok;
            QFont font =QFontDialog::getFont(&ok,this);
            if(ok){
            ui->tanswer_text->setFont(font);
             ui->tquestion_text->setFont(font);

             ui->card_list->setFont(font);

            }else return;
}







void MainWindow::on_actiontext_color_triggered()
{



            {
             // Get the selected text color using QColorDialog
             QColor textColor = QColorDialog::getColor(Qt::black, this, "Select Text Color");

             // If the user selected a color, update the text color for relevant components
             if (textColor.isValid()) {
            // Set text color for QLineEdit and QTextEdit using style sheets
            ui->tanswer_text->setStyleSheet(QString("color: %1;").arg(textColor.name()));
            ui->tquestion_text->setStyleSheet(QString("color: %1;").arg(textColor.name()));
             ui->add_text->setStyleSheet(QString("color: %1;").arg(textColor.name()));
               ui->label_date_time->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                 ui->label_2->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                   ui->back_button->setStyleSheet(QString("color: %1;").arg(textColor.name()));



                   ui->tabWidget->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                   ui->tanswer_label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                   ui->tquestion_label->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                   ui->pushButton_8->setStyleSheet(QString("color: %1;").arg(textColor.name()));

                   ui->add_text->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                   ui->clear_text->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                   ui->remove_text->setStyleSheet(QString("color: %1;").arg(textColor.name()));
                   ui->update_text->setStyleSheet(QString("color: %1;").arg(textColor.name()));


            // Set text color for QListWidget using style sheets

            ui->card_list->setStyleSheet(QString("color: %1;").arg(textColor.name()));
             }
            }




}


void MainWindow::on_actionbeckground_color_triggered()
{

            {
             // Get the selected background color using QColorDialog
             QColor bgColor = QColorDialog::getColor(Qt::white, this, "Select Background Color");

             // If the user selected a color, update the background color for relevant components
             if (bgColor.isValid()) {
            // Set background color for QLineEdit and QTextEdit using style sheets
            ui->tanswer_text->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->tquestion_text->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));

            // Set background color for QListWidget using style sheets

            ui->card_list->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->new_topic->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->new_topic_button->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->scrollArea->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));



            ui->clear_text->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->label_date_time->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->label_2->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->back_button->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));


            ui->tabWidget->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->tanswer_label->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->tquestion_label->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->pushButton_8->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));


            ui->remove_text->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
            ui->update_text->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));


            //ui->stackedWidget->setStyleSheet(QString("background-color: %1;").arg(bgColor.name()));
             }
            }

}


void MainWindow::on_actionbackground_triggered()
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


void MainWindow::on_actionnew_triggered()
{
            {
             MainWindow *newWindow = new MainWindow;
             newWindow->show();
            }

}



void MainWindow::on_new_topic_button_clicked()
{
            if(!ui->new_topic->text().isEmpty()){
             std::string path=(QString("flashcards/%1").arg(ui->new_topic->text())).toStdString();
             std::ifstream file;
             file.open(path);
             if(file){
                    //file exists error message
             }else{
             std::ofstream outfile;
            outfile.open(path);

            topics.push_back(ui->new_topic->text().toStdString());
             QFrame * fm=new QFrame;
            QHBoxLayout *horizontalLayout = new QHBoxLayout(fm);
            QPushButton * btn1=new QPushButton(ui->new_topic->text());
            horizontalLayout->addWidget(btn1);

            QPushButton * btn2=new QPushButton(QString("delete"));

           horizontalLayout->addWidget(btn2);
                ui->verticalLayout_5->addWidget(fm);
           std::string curtopic=ui->new_topic->text().toStdString();
            connect(btn1, &QPushButton::clicked, this, [=]() {
                // Your custom slot logic with parameters here
                goTopic(curtopic);
            });
                ui->new_topic->clear();
            connect(btn2, &QPushButton::clicked, this, [=]() {
                // Your custom slot logic with parameters here

                deleteTopic(curtopic,fm);
            });

             }




            }
}
void MainWindow::goTopic(std::string ctopic){

            topic=ctopic;
            questions.clear(); //remove all question from previous topic-> questions<vector>array
              ui->card_list->clear();//ui clear
            ui->label_2->setText(QString("Cards: %1").arg(QString::fromStdString(topic)));
             ui->tquestion_text->clear();
            //clear line text and planetext
              ui->tanswer_text->clear();
            load_cards();



            ui->stackedWidget->setCurrentIndex(0);


}
void MainWindow::deleteTopic(std::string ctopic,QFrame * frame){
            int index=0;
            for(int i=0;i<topics.size();i++){
             if(topics[i]==ctopic){
            index=i;
            break;
             }
            }
            frame->deleteLater();//button hatayo
            std::filesystem::remove("flashcards/"+topics[index]);//file hatayo
            topics.erase(topics.begin() + index);//list (vec array) bata hatayo



}

void MainWindow::on_back_button_clicked()
{

            ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::load_cards(){
            std::ifstream infile;
            infile.open("flashcards/"+topic);//open file containnign question and answer

            std::string line;
            while (std::getline(infile, line)) {//extract line by line from file.
             // Process each line
             std::stringstream ss(line);//create stream
             qna qs;
             std::getline(ss, qs.question, '~');
             //extract  and answer from line
             std::getline(ss, qs.answer, '~');
             questions.push_back(qs);//vec array (questions)

             QString displayText=QString("Question: %1").arg(QString::fromStdString(qs.question));
             ui->card_list->addItem(displayText);

//             std::cout<<qs.question.length()<<"//"<<qs.answer.length()<<std::endl;
            }
            infile.close();
}
void MainWindow::update_cards(){

     std::ofstream outfile;
     outfile.open("flashcards/"+topic);//open file for writing
     //all contents are erased


     //write content from vec array (questions) to file
     for(int i=0;i<questions.size();i++){
             outfile<<questions[i].question+"~"+questions[i].answer+"\n";

     }



     outfile.close();

}

