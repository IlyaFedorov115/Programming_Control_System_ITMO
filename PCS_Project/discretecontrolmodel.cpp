#include "discretecontrolmodel.h"
#include <iostream>

SimpleMatrix::SimpleMatrix(size_t rows, size_t columns, double initVal)
    : rows_(rows), columns_(columns)
{
    QVector<double> currRow = QVector<double>(columns_, initVal);
    for (int i = 0; i < rows_; i++){
        data_.push_back(currRow);
    }
}

double SimpleMatrix::getElem(size_t row, size_t col)
{
    return data_[row][col];
}

void SimpleMatrix::setElem(size_t row, size_t col, double value)
{
    data_[row][col] = value;
}

void SimpleMatrix::getSize(int &row, int &col)
{
    row = rows_; col = columns_;
}

size_t SimpleMatrix::getRows()
{
    return rows_;
}

size_t SimpleMatrix::getColumns()
{
    return columns_;
}

DiscreteControlModel::DiscreteControlModel(SimpleMatrix* A, QVector<double> B, QVector<double> C, double D, QVector<double> x, double y)
    : A_(A), B_(B), C_(C), D_(D), xCurr(x), yCurr(y)
{
    if (A_->getColumns() != A_->getRows() ||
            A_->getRows() != xCurr.size() ||
            A_->getRows() != B_.size() ||
            C_.size() != xCurr.size())
        throw DiscreteControlModelError();

}

double DiscreteControlModel::update(double val, double dt)
{
    auto currX = xCurr;
   // std::cout << "Currx : " << currX[0] << " " << currX[1] << " " << std::endl;

    /** recalc x[k+1] = A*x[k] + B*u(t) */
    for (int cRow = 0; cRow < xCurr.size(); cRow++)
    {
        xCurr[cRow] = B_[cRow] * val;
        for (int cCol = 0; cCol < A_->getColumns(); cCol++)
        {
            xCurr[cRow] += A_->getElem(cRow, cCol) * currX[cCol];
        }
    }

    /** recalc y by x[k] and return */
    auto currY = yCurr;
    yCurr = D_ * val;
    for (int i = 0; i < C_.size(); i++){
        yCurr += C_[i] * currX[i];
    }

    return yCurr;

    /** work version */

    /*
    double y = yCurr;
    auto x = xCurr;
    yCurr = 1.0 *x[0] + val;
    yCurr = C_[0]*x[0] + C_[1]*x[1] + C_[2]*x[2] + val;
    xCurr[0] = A_->getElem(0,0) * x[0] + A_->getElem(0,1) * x[1] + A_->getElem(0,2) * x[2] + B_[0] * val;
    xCurr[1] = A_->getElem(1,0) * x[0] + A_->getElem(1,1) * x[1] + A_->getElem(1,2) * x[2] + B_[1] * val;
    xCurr[2] = A_->getElem(2,0) * x[0] + A_->getElem(2,1) * x[1] + A_->getElem(2,2) * x[2] + B_[2] * val;
    */
}

double DiscreteControlModel::getState()
{
    return yCurr;
}

DiscreteControlModel::~DiscreteControlModel()
{
    delete A_;
}

