#include "tictactoe.h"

#include <QTextStream>
#include <QProcess>
#include <stdio.h>
#include <QDebug>

using std::cout;
using std::endl;


TicTacToe::TicTacToe(QObject *parent) : QObject(parent)
{
}

void TicTacToe::instructions(){

    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
    cout << "--where human brain is pit against silicon processor\n\n";

    cout << "Make your move known by entering a number, 0 - 8.  The number\n";
    cout << "corresponds to the desired board position, as illustrated:\n\n";

    cout << "       0 | 1 | 2\n";
    cout << "       ---------\n";
    cout << "       3 | 4 | 5\n";
    cout << "       ---------\n";
    cout << "       6 | 7 | 8\n\n";

    cout << "Prepare yourself, human.  The battle is about to begin.\n\n";

}

char TicTacToe::winner(const std::vector<char> &board){

    const int WINNING_ROWS[8][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6} };
    const int TOTAL_ROWS = 8;

    for(int row = 0; row < TOTAL_ROWS; ++row){

        if( (board[WINNING_ROWS[row][0]] != EMPTY) &&                              //Go through the rows of WINNING_ROWS and determine if board[x][y] is winner
                (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
                (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]) )
        {
            return board[WINNING_ROWS[row][0]]; //Return the character that has won
        }
    }

    //Check for tie. If no more empty spots, no more moves
    if(count(board.begin(), board.end(), EMPTY) == 0)
        return TIE;

    //No one has won yet
    return NO_ONE;




}

int TicTacToe::askNumber(std::string question, int high, int low){

    int number;
    do{
        std::cout << question << " (" << low << " - " << high << "): ";
        std::cin >> number;
    } while(number > high || number < low);
}

char TicTacToe::opponent(char piece){
    if(piece == X)
        return O;
    else
        return X;
}

void TicTacToe::humanMove(int move){

    board[move] = human;
    qDebug() << "move: " << move << endl;



//    if(winner(board) == NO_ONE)
//        computerMove(opponent(human));

}

void TicTacToe::computerMove(char computer){
    unsigned int move = 0;
    bool found = false;

    //if computer can win on next move, that�s the move to make
    while (!found && move < board.size())
    {
        if (isLegal(move))
        {
            //try move
            board[move] = computer;
            //test for winner
            found = winner(board) == computer;
            //undo move
            board[move] = EMPTY;
        }

        if (!found)
        {
            ++move;
        }
    }

    //otherwise, if opponent can win on next move, that's the move to make
    if (!found)
    {
        move = 0;
        char human = opponent(computer);

        while (!found && move < board.size())
        {
            if (isLegal(move))
            {
                //try move
                board[move] = human;
                //test for winner
                found = winner(board) == human;
                //undo move
                board[move] = EMPTY;
            }

            if (!found)
            {
                ++move;
            }
        }
    }

    //otherwise, moving to the best open square is the move to make
    if (!found)
    {
        move = 0;
        unsigned int i = 0;

        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
        //pick best open square
        while (!found && i <  board.size())
        {
            move = BEST_MOVES[i];
            if (isLegal(move))
            {
                found = true;
            }

            ++i;
        }
    }


    qDebug() << "computer move: " << move << endl;
    board[move] = opponent(human);
    emit computerMove((int)move); //ambiguous


    //Check if winning move

}


bool TicTacToe::isLegal(int move) const{
    qDebug() << "wut: " << board[move] << endl;
    return (board[move] == (int)EMPTY);
}


void TicTacToe::Play(){


}

char TicTacToe::winner(){

    const int WINNING_ROWS[8][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6} };
    const int TOTAL_ROWS = 8;

    for(int row = 0; row < TOTAL_ROWS; ++row){

        if( (board[WINNING_ROWS[row][0]] != EMPTY) &&                              //Go through the rows of WINNING_ROWS and determine if board[x][y] is winner
                (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
                (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]) )
        {
            return board[WINNING_ROWS[row][0]]; //Return the character that has won
        }
    }

    //Check for tie. If no more empty spots, no more moves
    if(count(board.begin(), board.end(), EMPTY) == 0)
        return TIE;

    //No one has won yet
    return NO_ONE;

}


void TicTacToe::reset(){
    board = std::vector<char>(NUM_SQUARES,EMPTY);
}
