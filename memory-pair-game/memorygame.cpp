#include "memorygame.h"
#include "ui_memorygame.h"
#include <utility>
#include <numeric>
#include <ctime>
#include <QTimer>

enum gameStatus {FIRST_PICK, SECOND_PICK};
int remainingCards = 24;
std::vector< std::vector<char> > table;
gameStatus status = FIRST_PICK;
void resetTable();
QPushButton* firstPickedButton;
QPushButton *buttons[4][6];



memorygame::memorygame(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::memorygame)
{
    ui->setupUi(this);

    resetTable(); // Global olarak tanimladigim table degiskenini resetliyor, butonlara dokunmuyor.

    for(unsigned int i = 0; i < 4; i++){
        for(unsigned int j = 0; j < 6; j++){
            QString buttonName = "pushButton_" + QString::number(i) + QString::number(j); // Butonları ismine göre bulup sonra eşlenen yere koyuyoruz.
            QPushButton* button = this->findChild<QPushButton *>(buttonName);
            buttons[i][j] = button;
            button->setText("");
            connect(button, SIGNAL(released()), this, SLOT(buttonClicked()));  //tüm butonları aynı fonksiyona bağladım. birine tıklanınca buttonClicked() çalışacak.
        }
    }

    QPushButton* resetButton = this->findChild<QPushButton *>("ResetButton"); // reset butonu.
    connect(resetButton, SIGNAL(released()), this, SLOT(resetClicked()));   // bunun fonksiyonu ayrı, bunu yazmadım daha.
}

void memorygame::buttonClicked(){   // reset butonu hariç bir butona tıklanınca buraya giriyor.

    QPushButton* button = (QPushButton *)sender(); // tıklanılan butonu buluyor.

    if(status == FIRST_PICK){

        firstPickedButton = button;

        // butonun içine yazılması gereken değeri table'dan bulup içine yazıyor.
        button->setText(QChar(table[firstPickedButton->objectName().at(11).digitValue()][firstPickedButton->objectName().at(12).digitValue()]));

        status = SECOND_PICK;

    }else { // SECOND_PICK İSE

        QChar secondPickedLetter = QChar(table[button->objectName().at(11).digitValue()][button->objectName().at(12).digitValue()]);

        // İki butonun içindeki değeri table'dan bulup karşılaştırıyor. Aynı ise butonları siliyor. Farklı ise butonların textini siliyor, yani kartı kapatıyor.
        if(firstPickedButton->text() == secondPickedLetter && firstPickedButton != button){

            //WAIT
            // WAIT icin bunu kullanabiliriz, ama beceremedim. --> QTimer::singleShot(200, this, SLOT(updateCaption()));
            button->setText(secondPickedLetter);
            firstPickedButton->setEnabled(0);
            button->setEnabled(0);
            remainingCards -= 2;

        }else {

            button->setText(secondPickedLetter);
            QTimer::singleShot(1000, []{});
            button->setText("");
            firstPickedButton->setText("");

        }
        status = FIRST_PICK;
    }
}

void memorygame::resetClicked(){

    resetTable();

    // Kartları 3 saniye göster, WAIT.

    for(unsigned int i = 0; i < 4; i++){
        for(unsigned int j = 0; j < 6; j++){
            buttons[i][j]->setDisabled(0);
            buttons[i][j]->setText("");
        }
    }


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
