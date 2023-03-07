#include "controller.h"
#include <QDebug>
#include <cstring>

Controller::Controller()
{

}

void Controller::process(QByteArray data)
{
    qDebug() << data.toHex(' '); // первый байт не меняется
    // заголовок 2 байта в начале и контрольная сумма в конце

    // понять что за высота
    float altitude;

    std::memcpy(&altitude, data.data() + 2, 4);
    qDebug() << altitude;


    char sum = 0x00; // тут будем суммировать

    for (int i = 0; i < data.size(); i++){
        sum += *reinterpret_cast<quint8*>(data.data() + i);
    }

    if (sum == char(0xFF)){

    } else {
        qDebug() << "Error";
    }


    // better quint8 sum and sum
}
