#include "ultimate_ttt_ui.h"
#include "./ui_ultimate_ttt_ui.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>

Ultimate_TTT_UI::Ultimate_TTT_UI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Ultimate_TTT_UI)
{
    ui->setupUi(this);

    player1 = true;
    player2 = false;

    ultimateBoard = new Ultimate_Board<char>();

    getPlayersInfo();

    //ULTIMATE_TTT_GAME = new GameManager<char>(ultimateBoard, players);

    // updateNoOfMoves();
}

Ultimate_TTT_UI::~Ultimate_TTT_UI()
{
    delete ui;

    if (players[0]) delete players[0];
    if (players[1]) delete players[1];
    if (ultimateBoard) delete ultimateBoard;

    //delete ULTIMATE_TTT_GAME;
}

void Ultimate_TTT_UI::getPlayersInfo(){
    QString player1Name = QInputDialog::getText(this, "Player 1 Name", "Enter Player 1 name:", QLineEdit::Normal, "Player 1");
    if(player1Name.isEmpty()) player1Name = "Player1";

    QChar player1Symbol = getSymbol("X");

    players[0] = new Ultimate_TTT_Player<char>(player1Name.toStdString(), player1Symbol.toLatin1());

    QMessageBox msgBox(this);

    msgBox.setText("Choose your opponent type:");
    // QPushButton* aiButton = msgBox.addButton("AI Player", QMessageBox::ActionRole);
    // QPushButton* randomButton = msgBox.addButton("Random Computer Player", QMessageBox::ActionRole);
    QPushButton* realButton = msgBox.addButton("Real Player", QMessageBox::ActionRole);

    msgBox.exec();

    QChar player2Symbol;

    /*if (msgBox.clickedButton() == aiButton) {
        player2Symbol = getSymbol("O");
        players[1] = new P_TTT_AI_Player<char>(player2Symbol.toLatin1());
        players[1]->setBoard(Board);
        nonHumanPlayerMode = true;
    } else if (msgBox.clickedButton() == randomButton) {
        player2Symbol = getSymbol("O");
        players[1] = new P_TTT_Random_Player<char>(player2Symbol.toLatin1());
        nonHumanPlayerMode = true;
    } else */if (msgBox.clickedButton() == realButton) {
        QString player2Name = QInputDialog::getText(this, "Player 2 Name", "Enter Player 2 name:", QLineEdit::Normal, "Player 2");
        if (player2Name.isEmpty()) player2Name = "Player 2";

        player2Symbol = getSymbol("O");

        players[1] = new Ultimate_TTT_Player<char>(player2Name.toStdString(), player2Symbol.toLatin1());
    }

    // ui->name1Label->setText("Name: " + QString::fromStdString(players[0]->getname()));
    // ui->mark1Label->setText("Mark: " + QString::fromStdString(string(1, players[0]->getsymbol())));

    // ui->name2label->setText("Name: " + QString::fromStdString(players[1]->getname()));
    // ui->mark2Label->setText("Mark: " + QString::fromStdString(string(1, players[1]->getsymbol())));
}

QChar Ultimate_TTT_UI::getSymbol(const QString& defaultSymbol){
    QChar playerSymbol;
    while (true) {
        QString symbolInput = QInputDialog::getText(this, "Player 1 Symbol", "Enter Player 1 symbol (one character):", QLineEdit::Normal, defaultSymbol);
        if (symbolInput.size() == 1 && !symbolInput.at(0).isSpace()) {
            playerSymbol = symbolInput.at(0);
            break;
        } else {
            QMessageBox::warning(this, "Invalid Input", "Player 1 symbol must be a single non-whitespace character.");
        }
    }
    return playerSymbol;
}

void Ultimate_TTT_UI::toggle(const int& i, const int& j){
    if(i == 0 && j == 0) ui->_0_0_Grid->setEnabled(false);
    if(i == 0 && j == 1) ui->_0_1_Grid->setEnabled(false);
    if(i == 0 && j == 2) ui->_0_2_Grid->setEnabled(false);
    if(i == 1 && j == 0) ui->_1_0_Grid->setEnabled(false);
    if(i == 1 && j == 1) ui->_1_1_Grid->setEnabled(false);
    if(i == 1 && j == 2) ui->_1_2_Grid->setEnabled(false);
    if(i == 2 && j == 0) ui->_2_0_Grid->setEnabled(false);
    if(i == 2 && j == 1) ui->_2_1_Grid->setEnabled(false);
    if(i == 2 && j == 2) ui->_2_2_Grid->setEnabled(false);

}

void Ultimate_TTT_UI::toggleLocalBoards(){
    if(ultimateBoard->currentBoard_X == -1 || ultimateBoard->currentBoard_Y == -1) return;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(i != ultimateBoard->currentBoard_X && ultimateBoard->currentBoard_Y)
                toggle(i, j);
        }

    }
}


