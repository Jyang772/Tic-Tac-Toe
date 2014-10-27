#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog.h"
#include "tictactoe.h"
#include <string.h>
#include <iostream>
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setChar(char);
    void Play();
    void CheckWinner();

    ~MainWindow();

signals:
    void turnComplete(int);

private slots:
    void itemClicked();
    void begin();

    void humanMoves();
    void invalidMove();
    void computerMove(int);


    void on_playAgain_clicked();

private:
    Ui::MainWindow *ui;
    Dialog *options = new Dialog;

    QPushButton *itemButtons[9];
    QPushButton *createButton(QString&, const QString/*const char**/);

    TicTacToe *game = new TicTacToe();

    bool humanTurn;
};

#endif // MAINWINDOW_H
