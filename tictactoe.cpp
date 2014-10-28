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



int TicTacToe::opponent(int piece){
    if(piece == -1)
        return 1;
    else
        return -1;
}

void TicTacToe::humanMove(int move){

    qDebug() << "gridChar: " << human << endl;

    board[move] = human;
    qDebug() << "move: " << move << endl;
    qDebug() << "gridChar: " << human << endl;


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

        //const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
        const int BEST_MOVES[] = {3, 5, 2, 6, 8, 1, 0, 5, 7};

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

int TicTacToe::winner(const std::vector<int> &board){

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

    //No one has won yet
    return 0;
}

int TicTacToe::winner(){

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
            qDebug() << "column 1: " << board[1] << endl;
            return board[WINNING_ROWS[row][0]]; //Return the character that has won
        }
    }

    //Check for tie. If no more empty spots, no more moves
    if(count(board.begin(), board.end(), EMPTY) == 0)
        //return TIE;
        return 0;


}


void TicTacToe::reset(){
    board = std::vector<int>(NUM_SQUARES,EMPTY);
}

int TicTacToe::minimax(std::vector<int> &board, int player){
    //printf("Entered minimax. player: %d\n", player);
    //qDebug() << "Entered minimax. player: " << player << endl;

    //How is the position like for player (their turn) on board?
    int win = winner(board);
    if(win != 0)
    {
        return win*player;
    }

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == EMPTY) {//If legal,
            board[i] = player;//Try the move

            int thisScore = -minimax(board, player*-1);
            //printf("thisScore: %d, score: %d, player: %d\n",thisScore,score,player);
            //qDebug() << "player*-1: " << player *-1 << endl;
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try

        }
    }

    if(move == -1) return 0;
    return score;

}

void TicTacToe::computerMax(){
    //qDebug() << "Inside computerMax()\n";
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == EMPTY) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;

    //board[move] = opponent(human);
    emit computerMove(move); //ambiguous

}

char TicTacToe::gridChar(int i) {
    switch(i) {
    case -1:
        return 'X';
    case 0:
        return ' ';
    case 1:
        return 'O';
    }

    return 0;
}
