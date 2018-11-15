#include "gamelogic.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameLogic w;
    w.show();

    return a.exec();
}
