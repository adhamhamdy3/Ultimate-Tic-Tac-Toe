#ifndef ULTIMATE_TTT_UI_H
#define ULTIMATE_TTT_UI_H

#include <QMainWindow>
#include "BoardGame_Classes.h"
#include "Ultimate_Tic_Tac_Toe.h"
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class Ultimate_TTT_UI;
}
QT_END_NAMESPACE

class Ultimate_TTT_UI : public QMainWindow
{
    Q_OBJECT

public:
    Ultimate_TTT_UI(QWidget *parent = nullptr);
    ~Ultimate_TTT_UI();

private slots:
    void on__0_0_Grid_cellDoubleClicked(int row, int column);

private:
    Ui::Ultimate_TTT_UI *ui;
    Player<char>* players[2];
    Ultimate_Board<char>* ultimateBoard;
    //GameManager<char>* ULTIMATE_TTT_GAME;

private:
    bool player1, player2;

    bool gameOver;

    void getPlayersInfo();

    QChar getSymbol(const QString& defaultSymbol);

    void keepCurrentBoard();

    void turnON(const int&, const int&);
    void turnOFF(const int&, const int&);
    void turnON_ALL();
    void turnOFF_ALL();

    void updateCell(QTableWidgetItem*, const int&, const int&, const int&);

    void isGameIsOver();
};
#endif // ULTIMATE_TTT_UI_H
