#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTimer>
#include "qframe.h"
#include "qna.cpp"
#include <iostream>
QT_BEGIN_NAMESPACE
namespace Ui { class Flash_card; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    std::vector <qna> questions; //array of questions
    std::vector <std::string> topics; //array of topics
    void load_cards();
    void update_cards();
    std::string topic;//memorize current topic
public:
     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void timefunction();
    void addTextToList();
    void on_card_list_itemSelectionChanged();
//    void updateQuestionsAndAnswers();

    // Declare the custom signal
//signals:
//    void updateSignal();

private slots:
    void on_pushButton_8_clicked();

    void on_add_text_clicked();
    void on_update_text_clicked();
    void on_remove_text_clicked();
    void on_clear_text_clicked();
    void on_actionFont_triggered();
    void on_actiontext_color_triggered();
    void on_actionbeckground_color_triggered();
    void on_actionbackground_triggered();
    void on_actionnew_triggered();

    void goTopic(std::string);
    void deleteTopic(std::string,QFrame *);

    void on_new_topic_button_clicked();

    void on_back_button_clicked();

private:
    Ui::Flash_card *ui;
    QTimer *timer;
};

#endif // MAINWINDOW_H
