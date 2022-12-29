#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QDateTime>
#include "qcustomplot.h"
#include "blocks/gain/gain.h"
#include "lintegrator.h"
#include "controlmodel.h"
#include "discretecontrolmodel.h"

class Generator;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void update();

private:
   // void updateDraw();

    Ui::Widget *ui;
    QGridLayout *mainlayout;
    QCustomPlot *inputPlot;
    QCustomPlot *outputPlot;
	QPushButton* startButton;
	QPushButton* saveButton;

	qint64 startTime = 0;
	qint64 relativeTime = 0;
	qint64 dt;

    QTimer * timer;

    // --------------------------
    // Add pointer to the object here
    // --------------------------
    Gain *object;   // <=
    LIntegrator* intergrator;
    Generator* generator;
    ControlModel* controlModel;
    DiscreteControlModel* discreteModel;
    DiscreteControlModel* discreteGenerator;
    // --------------------------
    // Add pointer to the object here
    // --------------------------
};

#endif // WIDGET_H
