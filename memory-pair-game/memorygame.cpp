#include "memorygame.h"
#include "ui_memorygame.h"
#include <utility>
#include <numeric>

enum gameStatus {FIRST_PICK, SECOND_PICK};
int remainingCards = 24;
std::vector< std::vector<char> > table;
gameStatus status = FIRST_PICK;
void resetTable();
QString firstPickedLetter;
QPushButton* firstPickedButton;

memorygame::memorygame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::memorygame)
{
    ui->setupUi(this);

    QPushButton *buttons[4][6];
    resetTable();

    for(unsigned int i = 0; i < 4; i++){
        for(unsigned int j = 0; j < 6; j++){
            QString buttonName = "pushButton_" + QString::number(i) + QString::number(j);
            buttons[i][j] = this->findChild<QPushButton *>(buttonName);
            buttons[i][j]->setText(QChar(table[i][j]));

            connect(buttons[i][j], SIGNAL(released()), this, SLOT(buttonClicked()));
        }
    }

    QPushButton* resetButton = this->findChild<QPushButton *>("ResetButton");
    connect(resetButton, SIGNAL(released()), this, SLOT(resetClicked()));
}

void memorygame::buttonClicked(){

    QPushButton* button = (QPushButton *)sender();
    if(status == FIRST_PICK){
        firstPickedLetter = button->text();
        firstPickedButton = button;
        button->setText("");
        status = SECOND_PICK;
    }else {
        if(firstPickedLetter == button->text()){
            firstPickedButton->hide();
            button->hide();
            remainingCards -= 2;
        }else {
            firstPickedButton->setText("OLD");
            button->setText("OLD");
        }
        status = FIRST_PICK;
    }

    button->objectName();

}

void memorygame::resetClicked(){
    QPushButton* button = (QPushButton *)sender();
    button->setText("OK");

}



memorygame::~memorygame()
{
    delete ui;
}



std::pair<std::pair<int, int>, char> randomChar(std::vector<char>& charVector, std::vector<int>& intVector){
    srand(time(0));
    int randCharIndex = rand()%charVector.size();
    char randChar = charVector[randCharIndex];
    charVector.erase(charVector.begin() + randCharIndex);

    int randIntIndex1 = rand()%intVector.size();
    int randIndex1 = intVector[randIntIndex1];
    intVector.erase(intVector.begin() + randIntIndex1);

    int randIntIndex2 = rand()%intVector.size();
    int randIndex2 = intVector[randIntIndex2];
    intVector.erase(intVector.begin() + randIntIndex2);

    std::pair<int, int> first(randIndex1, randIndex2);
    char second = randChar;

    return std::pair<std::pair<int, int>, char>(first, second);
}

void resetTable(){
    srand(time(0));
    table.clear();
    remainingCards = 24;
    status = FIRST_PICK;

    std::vector<char> charVector(26);
    std::iota(charVector.begin(), charVector.end(), 'A');

    std::vector<int> intVector;
    for (int i = 0; i < 24; i++) {
        intVector.push_back(i);
    }
    for (unsigned int i = 0; i < 4; i++) {
        std::vector<char> row;
        table.push_back(row);
        for (unsigned int j = 0; j < 6; j++) {
            table[i].push_back('0');
        }
    }

    for (int i = 0; i < 12; i++) {
        char letter;
        std::pair<int, int> indexPair;
        std::pair<std::pair<int, int>, char> randoms = randomChar(charVector, intVector);
        letter = randoms.second;
        indexPair = randoms.first;
        int index1_row = indexPair.first/6;
        int index1_col = indexPair.first%6;
        int index2_row = indexPair.second/6;
        int index2_col = indexPair.second%6;
        table[index1_row][index1_col] = letter;
        table[index2_row][index2_col] = letter;
    }

}
