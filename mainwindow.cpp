#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    humanTurn = false;

    ui->playAgain->setVisible(false);

    options->setWindowFlags(Qt::WindowStaysOnTopHint);
    options->setModal(true);
    options->show();


    for(int i=0; i<9; i++){
        QString text = "";
        //        itemButtons[i] = new QPushButton();
        //        connect(itemButtons[i],SIGNAL(clicked()),this,SLOT(itemClicked()));
        itemButtons[i] = createButton(text,SLOT(itemClicked()));
        itemButtons[i]->setObjectName(QString::number(i));
    }

    for(int i=0; i<9; i++){
        int row = i/3;
        int column = i%3;
        ui->gridLayout->addWidget(itemButtons[i],row,column);
    }


    connect(options,SIGNAL(choosen()),this,SLOT(begin()));
    connect(game,SIGNAL(humanMoves()),this,SLOT(humanMoves()));
    connect(game,SIGNAL(computerMove(int)),this,SLOT(computerMove(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

QPushButton *MainWindow::createButton(QString &text, const QString member/*const char *member*/){
    //Creates button and sets size policy. Connects button's signal to slot

    QPushButton *button = new QPushButton;
    button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button->setText(text);
    button->setCheckable(true);
    button->setAutoExclusive(true);



    connect(button, SIGNAL(clicked()),this,member.toStdString().c_str()); //connect button signal to SLOT(itemClicked)
    return button;
}

void MainWindow::itemClicked(){
    //Slot for when a tile has been clicked.


    qDebug() << "ItemClicked\n";
    QPushButton *clickedItem = qobject_cast<QPushButton*>(sender());
    clickedItem->setAutoExclusive(false);
    clickedItem->setChecked(false);
    clickedItem->setAutoExclusive(true);

    //Read user symbol, and set button to that symbol
    if(humanTurn && game->isLegal(clickedItem->objectName().toInt())){
        clickedItem->setText(QString(QChar(game->human)));
        game->humanMove(clickedItem->objectName().toInt());
        //Check if player has won.
        CheckWinner();
    }
    else if(!game->isLegal(clickedItem->objectName().toInt()))
        invalidMove();
}

void MainWindow::begin(){
    //Sets player character. Calls TicTacToe::Play()
    //The Game begins.

    QString text = "You are playing as " + QString(QChar(options->getChar()));
    if(options->getChar() == 'O'){

        text.append(". Computer moves first.");
        game->human = 'O';

        //Computer makes move
        game->computerMove(game->opponent(game->human));
    }
    else{
        text.append(". Select a square.");
        game->human = 'X';
        humanTurn = true;
    }

    ui->announce->setText(text);


    //Begin game
    //game->Play();


}

void MainWindow::humanMoves(){

    humanTurn = true;
    ui->announce->setText("Make a move.");
}

void MainWindow::computerMove(int move){

    humanTurn = false;
    itemButtons[move]->setText(QString(QChar(game->opponent(game->human))));
    //Check if computer has won
    CheckWinner();
}

void MainWindow::CheckWinner(){

    if(game->winner() == game->human){
        ui->announce->setText("You have won!");
        humanTurn = false; //Disable clicking
        ui->playAgain->setVisible(true);
        return;
    }
    else if(game->winner() == game->opponent(game->human)){
        ui->announce->setText("You have lost!");
        ui->playAgain->setVisible(true);
        return;
    }
    else if(game->winner() == 'T'){
        ui->announce->setText("TIE!");
        ui->playAgain->setVisible(true);
        return;
    }

    if(humanTurn)
        game->computerMove(game->opponent(game->human));
    else
        humanMoves();
}

void MainWindow::invalidMove(){
    ui->announce->setText("Invalid move! Try again.");
}

void MainWindow::on_playAgain_clicked()
{
    for(int i=0; i<9; i++)
        itemButtons[i]->setText("");

    game->reset();
    begin();

}
