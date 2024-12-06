#ifndef ULTIMATE_TTT_UI_H
#define ULTIMATE_TTT_UI_H

#include <QMainWindow>
#include "BoardGame_Classes.h"
#include "Ultimate_Tic_Tac_Toe.h"

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

private:
    Ui::Ultimate_TTT_UI *ui;
    Player<char>* players[2];
    Ultimate_Board<char>* ultimateBoard;
    //GameManager<char>* ULTIMATE_TTT_GAME;

private:
    bool player1, player2;

    void getPlayersInfo();

    QChar getSymbol(const QString& defaultSymbol);

    void toggleLocalBoards();

    void toggle(const int&, const int&);
};
#endif // ULTIMATE_TTT_UI_H
