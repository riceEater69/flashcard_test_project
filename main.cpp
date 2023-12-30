
#include "mainwindow.h"

#include <QApplication>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;//create folder

int main(int argc, char *argv[])
{
    if (fs::create_directory("flashcards"))
        std::cout << "Folder created successfully." << std::endl;
    else
        std::cerr << "Failed to create folder." << std::endl;
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("flash cards");
    w.show();
    return a.exec();
}
