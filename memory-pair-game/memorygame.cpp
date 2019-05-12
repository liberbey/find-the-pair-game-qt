#include "memorygame.h"
#include "ui_memorygame.h"

memorygame::memorygame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::memorygame)
{
    ui->setupUi(this);
}

memorygame::~memorygame()
{
    delete ui;
}
