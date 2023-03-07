#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QByteArray>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();

public slots:
    void process(QByteArray data);

};

#endif // CONTROLLER_H
