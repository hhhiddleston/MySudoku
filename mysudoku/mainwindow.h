#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPalette>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setGrid(char arr[9][9]);
    void copyGrid(char arr[9][9]);

private slots:
    void squareClicked();
    void numberClicked();
    void solveClicked();
    void clearClicked();
    void emtyClicked();
    void easyClicked();
    void middleClicked();
    void hardClicked();
    void helpClicked();
    void display();

private:
    QPushButton *square[9][9];
    QPushButton *number[9];
    QPushButton *emtyButton;
    QPushButton *solveButton;
    QPushButton *clearButton;
    QPushButton *TrymyselfButton;
    QPushButton *easyButton;
    QPushButton *middleButton;
    QPushButton *hardButton;
    QPushButton *helpButton;

    QPalette *redText;
    QPalette *whiteText;
    QPalette *blackText;

    QString value;
    char grid[9][9];


    void setSquareGeo();
    void setNumberGeo();
};

#endif // MAINWINDOW_H
