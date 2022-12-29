#include "widget.h"
#include "ui_widget.h"
#include "generator.h"
#include "constans.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <QVector>
// --------------------------
// Set stop time here
// --------------------------
#define ENDOFTIME 100
#define SAMPLINGTIMEMSEC 200

#define LEFT_Y_MIN -0
#define LEFT_Y_MAX 5

#define RIGHT_Y_MIN -0
#define RIGHT_Y_MAX 5

#define STEPS_GRAPH

// --------------------------
// Set stop time here
// --------------------------

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

	// Create dir for logs
	if (!QDir("logs").exists()) {
		QDir().mkdir("logs");
	}

    // Set window size
	this->setMinimumSize(640, 480);

    // Add main layout with two plots
    mainlayout = new QGridLayout(this);
    inputPlot = new QCustomPlot(this);
    outputPlot = new QCustomPlot(this);
	mainlayout->addWidget(inputPlot, 0, 0);
	mainlayout->addWidget(outputPlot, 0, 1);
	inputPlot->addGraph();
	outputPlot->addGraph();

	startButton = new QPushButton("Start");
	connect(startButton, &QPushButton::clicked, this, [=](){
		startTime = 0;
		relativeTime = 0;
		inputPlot->graph(0)->data()->clear();
		outputPlot->graph(0)->data()->clear();
		timer->start();
	});
	mainlayout->addWidget(startButton, 1, 0);

	saveButton = new QPushButton("Save");
	connect(saveButton, &QPushButton::clicked, this, [=](){
		QString timestamp = QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss");
		inputPlot->savePng(QString("./logs/%1_input.png").arg(timestamp));
		outputPlot->savePng(QString("./logs/%1_output.png").arg(timestamp));
	});
	mainlayout->addWidget(saveButton, 1, 1);

    // Give the axes some labels:
    inputPlot->xAxis->setLabel("t");
    inputPlot->yAxis->setLabel("input");
    outputPlot->xAxis->setLabel("t");
    outputPlot->yAxis->setLabel("output");

    // --------------------------
    // Change ranges if you need
    // --------------------------
    // Set axes ranges so see all data:
    inputPlot->xAxis->setRange(0, ENDOFTIME);
    inputPlot->yAxis->setRange(LEFT_Y_MIN, LEFT_Y_MAX);
    outputPlot->xAxis->setRange(0, ENDOFTIME);
    outputPlot->yAxis->setRange(RIGHT_Y_MIN, RIGHT_Y_MAX);

    // --------------------------
    // Create the object here
    // --------------------------

    /** CREATE INTEGRATOR */

    object = new Gain(2.0);
    intergrator = new LIntegrator(-1.0);



    /** CREATE GENERATOR */
    std::vector<double> states_;
    states_.push_back(0.0); states_.push_back(1.0); states_.push_back(1.0);
    std::vector<double> gains_;
    gains_.push_back(-0.25); gains_.push_back(-0.5);
    generator = new Generator(states_, gains_);


    /** CREATE DISCRETE GENERATOR */
    QVector<double> xStGen {1.0, 0.0, 1.0};
    discreteGenerator = new DiscreteControlModel(getDGeneratorA1(), DGeneratorB, DGeneratorC, DGeneratorD, xStGen, 0.0);

    /** CREATE CONTROL MODEL */

    QVector<double> statesModel;
    statesModel.push_back(0.0);
    statesModel.push_back(0.0);
    statesModel.push_back(0.0);
    QVector<QPair<double, double>> gainsModel;
    gainsModel.push_back(QPair<double, double>(-4.0, 0.0));
    gainsModel.push_back(QPair<double, double>(-4.0, 0.0));
    gainsModel.push_back(QPair<double, double>(-1.0, 1.0));
    QPair<double, double> sigGain(1.0, 1.0);
    controlModel = new ControlModel(statesModel, gainsModel, sigGain);


    /** CREATE DISCRETE CONTROL MODEL */
    QVector<double> xSt {1.0, 1.0, 0.0};
    discreteModel = new DiscreteControlModel(getAdt1(), GpssConB1, GpssConC, GpssConD, xSt, 0.0);

    // --------------------------
    // Create the object here
    // --------------------------

    timer = new QTimer(this);
    timer->setTimerType(Qt::TimerType::PreciseTimer);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    // --------------------------
    // Set sampling time here
    // --------------------------
	timer->setInterval(SAMPLINGTIMEMSEC);
    // --------------------------
    // Set sampling time here
    // --------------------------
}

Widget::~Widget()
{
    delete ui;
    delete inputPlot;
    delete outputPlot;
    delete timer;
    delete mainlayout;

    // --------------------------
    // Delete the object here
    // --------------------------
    delete object;
    delete intergrator;
    delete generator;
    delete controlModel;
    delete discreteModel;
    // --------------------------
    // Delete the object here
    // --------------------------
}

void Widget::update() {

	double signal = std::sin(relativeTime / 1000.0);

	if (startTime == 0) {
		startTime = QDateTime::currentMSecsSinceEpoch();
		inputPlot->graph(0)->addData(0.0, 0);
		outputPlot->graph(0)->addData(0.0, 0);
		return;
	} else {
		dt = relativeTime;
		relativeTime = QDateTime::currentMSecsSinceEpoch() - startTime;
		dt = relativeTime - dt;
	}

    /** DRAW LEFT */
    //inputPlot->graph(0)->addData(relativeTime / 1000.0, signal);
    inputPlot->graph(0)->addData(relativeTime / 1000.0, this->controlModel->update(1, dt / 1000.0));


    /** DRAW RIGHT */
    //outputPlot->graph(0)->addData(relativeTime / 1000.0, object->update(signal));
    //outputPlot->graph(0)->addData(relativeTime / 1000.0, intergrator->update(signal, dt / 1000.0));
    //outputPlot->graph(0)->addData(relativeTime / 1000.0, generator->update(signal, dt / 1000.0));
    //outputPlot->graph(0)->addData(relativeTime / 1000.0, controlModel->update(signal, dt / 1000.0));

    // curr state рисовать чтобы получить
#ifdef STEPS_GRAPH
    outputPlot->graph(0)->addData(relativeTime / 1000.0, discreteModel->getState());
#endif
    outputPlot->graph(0)->addData(relativeTime / 1000.0, discreteModel->update(1, dt / 1000.0));

    inputPlot->replot();
    outputPlot->replot();

    // --------------------------
    // Update the object here
    // --------------------------
    object->update(signal);
    // --------------------------
    // Update the object here
    // --------------------------

	if (relativeTime / 1000.0 > ENDOFTIME) {
		timer->blockSignals(true);
		timer->stop();
		timer->blockSignals(false);
	}
}
