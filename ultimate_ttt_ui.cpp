#include "ultimate_ttt_ui.h"
#include "./ui_ultimate_ttt_ui.h"

Ultimate_TTT_UI::Ultimate_TTT_UI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Ultimate_TTT_UI)
{
    ui->setupUi(this);
}

Ultimate_TTT_UI::~Ultimate_TTT_UI()
{
    delete ui;
}
