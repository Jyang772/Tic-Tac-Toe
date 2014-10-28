#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <iostream>
#include <vector>
#include <QObject>

//global constants
const int NUM_SQUARES = 9;
const char X = 'X';
const char O = 'O';
//const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';
const int EMPTY = 0;

class TicTacToe : public QObject
{
    Q_OBJECT

public:
    explicit TicTacToe(QObject *parent = 0);
    //TicTacToe();
    void instructions();
    //void Play();

    int winner(const std::vector<int>& board); //Checks to see if anyone has won
    int winner();

    int opponent(int piece);
    void computerMove(char computer);
    bool isLegal(int move) const;

    int human;
    int turn;

    void reset();

    //Minimax
    void computerMax();
    int minimax(std::vector<int>& board,int player);
    char gridChar(int i);

signals:
    void humanMoves();
    void computerMove(int);

public slots:
    void humanMove(int);

private:
    //Compiler derps with initialization of aggregate members
    //std::vector<char> board{std::vector<char>(NUM_SQUARES,EMPTY)};
    std::vector<int> board = std::vector<int>(NUM_SQUARES,EMPTY);
};

#endif // TICTACTOE_H
