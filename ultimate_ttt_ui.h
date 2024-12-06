#ifndef ULTIMATE_TTT_UI_H
#define ULTIMATE_TTT_UI_H

#include <QMainWindow>

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
};
#endif // ULTIMATE_TTT_UI_H
