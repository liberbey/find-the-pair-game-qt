#ifndef MEMORYGAME_H
#define MEMORYGAME_H

#include <QMainWindow>

namespace Ui {
class memorygame;
}

class memorygame : public QMainWindow
{
    Q_OBJECT

public:
    explicit memorygame(QWidget *parent = nullptr);
    ~memorygame();

private:
    Ui::memorygame *ui;
};

#endif // MEMORYGAME_H
