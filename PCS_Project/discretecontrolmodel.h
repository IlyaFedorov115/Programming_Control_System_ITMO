#ifndef DISCRETECONTROLMODEL_H
#define DISCRETECONTROLMODEL_H

#include <QVector>

class SimpleMatrix{
public:
    SimpleMatrix(size_t rows, size_t columns,  double initVal=0.0);
    double getElem(size_t row, size_t col);
    void setElem(size_t row, size_t col, double value);
    void getSize(int& row, int& col);
    size_t getRows();
    size_t getColumns();

private:
    QVector<QVector<double>> data_;
    size_t rows_;
    size_t columns_;
};


class DiscreteControlModelError{};

class DiscreteControlModel
{
public:
    DiscreteControlModel(SimpleMatrix* A, QVector<double> B, QVector<double> C, double D, QVector<double> x, double y);
    double update(double val, double dt);
    double getState();
    ~DiscreteControlModel();

private:
    SimpleMatrix* A_;
    QVector<double> B_;
    QVector<double> C_;
    double D_;
    QVector<double> xCurr;           // x[k]
    double yCurr;           // y[k]

};

#endif // DISCRETECONTROLMODEL_H
