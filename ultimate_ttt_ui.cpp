#include "ultimate_ttt_ui.h"
#include "./ui_ultimate_ttt_ui.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>

Ultimate_TTT_UI::Ultimate_TTT_UI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Ultimate_TTT_UI)
{
    ui->setupUi(this);

    player1 = true;
    player2 = false;

    gameOver = false;

    nonHumanPlayerMode = false;

    ultimateBoard = new Ultimate_Board<char>();

    getPlayersInfo();

    // Initialize UI_labels
    UI_labels[0][0] = ui->_0_0_Label;
    UI_labels[0][1] = ui->_0_1_Label;
    UI_labels[0][2] = ui->_0_2_Label;
    UI_labels[1][0] = ui->_1_0_Label;
    UI_labels[1][1] = ui->_1_1_Label;
    UI_labels[1][2] = ui->_1_2_Label;
    UI_labels[2][0] = ui->_2_0_Label;
    UI_labels[2][1] = ui->_2_1_Label;
    UI_labels[2][2] = ui->_2_2_Label;

    // Initialize UI_grids
    UI_grids[0][0] = ui->_0_0_Grid;
    UI_grids[0][1] = ui->_0_1_Grid;
    UI_grids[0][2] = ui->_0_2_Grid;
    UI_grids[1][0] = ui->_1_0_Grid;
    UI_grids[1][1] = ui->_1_1_Grid;
    UI_grids[1][2] = ui->_1_2_Grid;
    UI_grids[2][0] = ui->_2_0_Grid;
    UI_grids[2][1] = ui->_2_1_Grid;
    UI_grids[2][2] = ui->_2_2_Grid;



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

    players[0] = new Ultimate_TTT_Player<char>(player1Name.toStdString(), player1Symbol.toLatin1(), ultimateBoard);

    QMessageBox msgBox(this);

    msgBox.setText("Choose your opponent type:");
    // QPushButton* aiButton = msgBox.addButton("AI Player", QMessageBox::ActionRole);
    QPushButton* randomButton = msgBox.addButton("Random Computer Player", QMessageBox::ActionRole);
    QPushButton* realButton = msgBox.addButton("Real Player", QMessageBox::ActionRole);

    msgBox.exec();

    QChar player2Symbol;

    /*if (msgBox.clickedButton() == aiButton) {
        player2Symbol = getSymbol("O");
        players[1] = new P_TTT_AI_Player<char>(player2Symbol.toLatin1());
        players[1]->setBoard(Board);
        nonHumanPlayerMode = true;
    } else*/ if (msgBox.clickedButton() == randomButton) {
        player2Symbol = getSymbol("O");
        players[1] = new Ultimate_TTT_Random_Player<char>(player2Symbol.toLatin1(), ultimateBoard);
        nonHumanPlayerMode = true;
    } else if (msgBox.clickedButton() == realButton) {
        QString player2Name = QInputDialog::getText(this, "Player 2 Name", "Enter Player 2 name:", QLineEdit::Normal, "Player 2");
        if (player2Name.isEmpty()) player2Name = "Player 2";

        player2Symbol = getSymbol("O");

        players[1] = new Ultimate_TTT_Player<char>(player2Name.toStdString(), player2Symbol.toLatin1(), ultimateBoard);
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

void Ultimate_TTT_UI::turnON_OFF(const int& i, const int& j, bool state){
    UI_grids[i][j]->setEnabled(state);
}


void Ultimate_TTT_UI::turnON_ALL(){
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            turnON_OFF(i, j, true);
        }
    }
}

void Ultimate_TTT_UI::turnOFF_ALL(){
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            turnON_OFF(i, j, false);
        }
    }
}

void Ultimate_TTT_UI::keepCurrentBoard(){
    if (ultimateBoard->currentBoard_X == -1 || ultimateBoard->currentBoard_Y == -1) return;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == ultimateBoard->currentBoard_X && j == ultimateBoard->currentBoard_Y) {
                turnON_OFF(i, j, true);
            } else {
                turnON_OFF(i, j, false);
            }
        }
    }
}

void Ultimate_TTT_UI::updateCell(QTableWidgetItem* item, const int& playerIndex, const int& row, const int& column){
    item->setText(QString::fromStdString(std::string(1, players[playerIndex]->getsymbol())));
    item->setTextAlignment(Qt::AlignCenter);
    item->setFont(QFont("Outrun future", 30, QFont::Bold));

    if(!playerIndex) item->setBackground(Qt::blue);
    else item->setBackground(Qt::red);

    item->setForeground(Qt::white);
    item->setFlags(Qt::NoItemFlags);

}

void Ultimate_TTT_UI::isGameIsOver(){
    if (ultimateBoard->game_is_over()) {
        if (ultimateBoard->is_win()) {
            if (player1)
                QMessageBox::information(this, "Win!", QString::fromStdString(players[0]->getname()) + " has won.");
            else
                QMessageBox::information(this, "Win!", QString::fromStdString(players[1]->getname()) + " has won.");
        } else if (ultimateBoard->is_draw()) {
            QMessageBox::information(this, "Draw!", "The match ended with a draw.");
        }
        gameOver = true;
    }
}

void Ultimate_TTT_UI::switchBoards(){
    if (ultimateBoard->canPickBoard) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                turnON_OFF(i, j, (ultimateBoard->localWinners[i][j] == ' '));
            }
        }
    } else {
        keepCurrentBoard();
    }
}

void Ultimate_TTT_UI::operate(QTableWidgetItem* item, const int& row, const int& column, const int& board_X, const int& board_Y){

    if(ultimateBoard->canPickBoard){
        ultimateBoard->currentBoard_X = board_X;
        ultimateBoard->currentBoard_Y = board_Y;
        switchBoards();
        ultimateBoard->canPickBoard = false;
    }

    int recentBoard_X = ultimateBoard->currentBoard_X;
    int recentBoard_Y = ultimateBoard->currentBoard_Y;
    int pIndx;

    if (player1) {
        ultimateBoard->update_board(row, column, players[0]->getsymbol());
        updateCell(item, 0, row, column);
        pIndx = 0;
    } else if (player2) {
        ultimateBoard->update_board(row, column, players[1]->getsymbol());
        updateCell(item, 1, row, column);
        pIndx = 1;
    }

    if(ultimateBoard->boards[recentBoard_X][recentBoard_Y]->winner != ' '){
        updateGridWinner(board_X, board_Y, pIndx);
    }

    isGameIsOver();

    if(gameOver) return void (turnOFF_ALL());

    switchBoards();

    player1 ^= 1;

    //player2 ^= 1;

    // updateState();

    if(!nonHumanPlayerMode) player2 ^= 1;

    if(nonHumanPlayerMode)
        nonHumanPlayerTurn(2000);

    updateNoOfMovesLabel();
}

void Ultimate_TTT_UI::on__0_0_Grid_cellDoubleClicked(int row, int column)
{
    if(!ui->_0_0_Grid->isEnabled()) return;

    QTableWidgetItem *item = ui->_0_0_Grid->item(row, column);

    operate(item, row, column, 0, 0);
}


void Ultimate_TTT_UI::on__0_1_Grid_cellDoubleClicked(int row, int column)
{
    if(!ui->_0_1_Grid->isEnabled()) return;

    QTableWidgetItem *item = ui->_0_1_Grid->item(row, column);

    operate(item, row, column, 0, 1);
}


void Ultimate_TTT_UI::on__0_2_Grid_cellDoubleClicked(int row, int column)
{
    if(!ui->_0_2_Grid->isEnabled()) return;

    QTableWidgetItem *item = ui->_0_2_Grid->item(row, column);

    operate(item, row, column, 0, 2);
}


void Ultimate_TTT_UI::on__1_0_Grid_cellDoubleClicked(int row, int column)
{
    if(!ui->_1_0_Grid->isEnabled()) return;

    QTableWidgetItem *item = ui->_1_0_Grid->item(row, column);

    operate(item, row, column, 1, 0);
}


void Ultimate_TTT_UI::on__1_1_Grid_cellDoubleClicked(int row, int column)
{
    if(!ui->_1_1_Grid->isEnabled()) return;

    QTableWidgetItem *item = ui->_1_1_Grid->item(row, column);

    operate(item, row, column, 1, 1);
}


void Ultimate_TTT_UI::on__1_2_Grid_cellDoubleClicked(int row, int column)
{
    if(!ui->_1_2_Grid->isEnabled()) return;

    QTableWidgetItem *item = ui->_1_2_Grid->item(row, column);

    operate(item, row, column, 1, 2);
}


void Ultimate_TTT_UI::on__2_0_Grid_cellDoubleClicked(int row, int column)
{
    if(!ui->_2_0_Grid->isEnabled()) return;

    QTableWidgetItem *item = ui->_2_0_Grid->item(row, column);

    operate(item, row, column, 2, 0);
}


void Ultimate_TTT_UI::on__2_1_Grid_cellDoubleClicked(int row, int column)
{
    if(!ui->_2_1_Grid->isEnabled()) return;

    QTableWidgetItem *item = ui->_2_1_Grid->item(row, column);

    operate(item, row, column, 2, 1);
}


void Ultimate_TTT_UI::on__2_2_Grid_cellDoubleClicked(int row, int column)
{
    if(!ui->_2_2_Grid->isEnabled()) return;

    QTableWidgetItem *item = ui->_2_2_Grid->item(row, column);

    operate(item, row, column, 2, 2);
}

void Ultimate_TTT_UI::updateNoOfMovesLabel() const{
    ui->noOfMoves_Label->setText("NUMBER OF MOVES = " +
                                 QString::fromStdString(std::to_string(ultimateBoard->n_moves)));

}

void Ultimate_TTT_UI::updateGridWinner(int gridX, int gridY, int playerIndex) {
    QLabel* label = nullptr;

    label = UI_labels[gridX][gridY];

    if (label) {
        label->setText(QString(players[playerIndex]->getsymbol()));
        label->setFont(QFont("Outrun future", 100, QFont::Bold));
        label->setAlignment(Qt::AlignCenter);

        QString baseStyle = QString(
                                "QLabel { "
                                "    background-color: %1; "
                                "    color: white; "
                                "    border-radius: 10px; "
                                "    transition: all 0.3s ease; "
                                "} "
                                "QLabel:hover { "
                                "    background-color: rgba(0, 0, 0, 0); "
                                "    color: rgba(255, 255, 255, 0.8); "
                                "    transform: scale(1.1); "
                                "}")
                                .arg(playerIndex == 0 ? "blue" : "red");

        label->setStyleSheet(baseStyle);

        label->raise();
        label->show();
    }
}


void Ultimate_TTT_UI::executeNonHumanPlayerTurn(){

    player1 = false;

    int x, y, board_X, board_Y;
    players[1]->getmove(x, y);

    while(!ultimateBoard->update_board(x, y, players[1]->getsymbol())){
        players[1]->getmove(x, y);
        board_X = ultimateBoard->currentBoard_X, board_Y = ultimateBoard->currentBoard_Y;
    }

    QTableWidgetItem *item = UI_grids[board_X][board_Y]->item(x, y);

    updateCell(item, 1, x, y);

    isGameIsOver();

    player1 = true;

    //updateState();

    if(gameOver){
        turnOFF_ALL();
        return;
    }

    switchBoards();
}

void Ultimate_TTT_UI::nonHumanPlayerTurn(const int &delay){
    turnOFF_ALL();
    QTimer::singleShot(delay, this, &Ultimate_TTT_UI::executeNonHumanPlayerTurn);
}

