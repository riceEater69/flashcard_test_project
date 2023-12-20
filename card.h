#ifndef CARD_H
#define CARD_H

#include <QDialog>
#include <QListWidget>
#include <vector>
#include "qna.cpp"
#include<QTimer>
namespace Ui {
class card;
}

class card : public QDialog
{
    Q_OBJECT
  int index;
    std::vector <qna>  card_list;
public:
    explicit card(std::vector <qna> *,QWidget *parent=nullptr);
    ~card();

    void setQuestionText(const QString &text);
    void setAnswerText(const QString &text);
    void newQuestion();

signals:
    void updateSignal(); // Add a new signal declaration

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();


    void on_start_clicked();

    void on_pause_clicked();

    void on_stop_clicked();
    void processor();

    void on_pushButton_7_clicked();

    void on_font_clicked();

    void on_textcolor_clicked();

    void on_background_color_clicked();

    void on_background_color2_clicked();

private:
    Ui::card *ui;
    short int minute;
    short int second;
    bool pauser;
    QTimer clock;


};

#endif // CARD_H
