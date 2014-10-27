#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <vector>
#include <QObject>

//global constants
const int NUM_SQUARES = 9;
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

class TicTacToe : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToe(QObject *parent = 0);
    //TicTacToe();
    void instructions();
    void Play();

    char winner(const std::vector<char>& board); //Checks to see if anyone has won
    char winner();
    int askNumber(std::string question, int high, int low = 0);

    char opponent(char piece);
    void computerMove(char computer);
    bool isLegal(int move) const;
    char human;
    char turn;

    void reset();

signals:
    void humanMoves();
    void computerMove(int);

public slots:
    void humanMove(int);

private:
    //Compiler derps with initialization of aggregate members
    //std::vector<char> board{std::vector<char>(NUM_SQUARES,EMPTY)};
    std::vector<char> board = std::vector<char>(NUM_SQUARES,EMPTY);
};

#endif // TICTACTOE_H
