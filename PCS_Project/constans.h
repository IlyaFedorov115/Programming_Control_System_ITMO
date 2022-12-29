#ifndef CONSTANS_H
#define CONSTANS_H

#include <QVector>
#include "discretecontrolmodel.h"


/** Matrixes for Discrete Generator */

SimpleMatrix* getDGeneratorA1()
{
    SimpleMatrix* result = new SimpleMatrix(3, 3);
    result->setElem(0, 0, 0.99500417); result->setElem(0, 1, 0.19966683); result->setElem(0, 2, 0.00000000);
    result->setElem(1, 0, -0.04991671); result->setElem(1, 1, 0.99500417); result->setElem(1, 2, 0.00000000);
    result->setElem(2, 0, 0.00000000); result->setElem(2, 1, 0.00000000); result->setElem(2, 2, 0.90483742);
    return result;
}


SimpleMatrix* getDGeneratorA2()
{
    SimpleMatrix* result = new SimpleMatrix(3, 3);
    result->setElem(0, 0, 0.99986388); result->setElem(0, 1, 0.03299850); result->setElem(0, 2, 0.00000000);
    result->setElem(1, 0, -0.00824963); result->setElem(1, 1, 0.99986388); result->setElem(1, 2, 0.00000000);
    result->setElem(2, 0, 0.00000000); result->setElem(2, 1, 0.00000000); result->setElem(2, 2, 0.98363538);
    return result;
}



SimpleMatrix* getDGeneratorA3()
{
    SimpleMatrix* result = new SimpleMatrix(3, 3);
    result->setElem(0, 0, 0.99998750); result->setElem(0, 1, 0.00999996); result->setElem(0, 2, 0.00000000);
    result->setElem(1, 0, -0.00249999); result->setElem(1, 1, 0.99998750); result->setElem(1, 2, 0.00000000);
    result->setElem(2, 0, 0.00000000); result->setElem(2, 1, 0.00000000); result->setElem(2, 2, 0.99501248);
    return result;
}


QVector<double> DGeneratorB {0.0, 0.0, 0.0};
QVector<double> DGeneratorC {1.0, 0.0, 1.0};
double DGeneratorD = 0.0;



/** Matrixes For Discrete Control object */

SimpleMatrix* getAdt1()
{
    SimpleMatrix* result = new SimpleMatrix(3, 3);
    result->setElem(0, 0, 0.998904057); result->setElem(0, 1, 0.195559240); result->setElem(0, 2, 0.015385936);
    result->setElem(1, 0, -0.015385936); result->setElem(1, 1, 0.937360312); result->setElem(1, 2, 0.134015495);
    result->setElem(2, 0, -0.134015495); result->setElem(2, 1, -0.551447918); result->setElem(2, 2, 0.401298331);
    return result;
}

SimpleMatrix* getAdt2()
{
    SimpleMatrix* result = new SimpleMatrix(3, 3);
    result->setElem(0, 0, 0.999994204); result->setElem(0, 1, 0.032976769); result->setElem(0, 2, 0.000521124);
    result->setElem(1, 0, -0.000521124); result->setElem(1, 1, 0.997909707); result->setElem(1, 2, 0.030892272);
    result->setElem(2, 0, -0.030892272); result->setElem(2, 1, -0.124090211); result->setElem(2, 2, 0.874340620);
    return result;
}

SimpleMatrix* getAdt3()
{
    SimpleMatrix* result = new SimpleMatrix(3, 3);
    result->setElem(0, 0, 0.999999835); result->setElem(0, 1, 0.009999340); result->setElem(0, 2, 0.000049338);
    result->setElem(1, 0, -0.000049338); result->setElem(1, 1, 0.999802482); result->setElem(1, 2, 0.009801986);
    result->setElem(2, 0, -0.009801986); result->setElem(2, 1, -0.039257284); result->setElem(2, 2, 0.960594536);
    return result;
}


/** For ALL */
QVector<double> GpssConC {1.0, 0.0, 0.0};
double GpssConD = 1.0;

/** dt-1 */


QVector<double> GpssConB1 {0.001095943, 0.015385936, 0.134015495};


/** dt-2 */
QVector<double> GpssConB2 {0.000005796, 0.000521124, 0.030892272};


/** dt-3 */
QVector<double> GpssConB3 {0.000000165, 0.000049338, 0.009801986};



#endif // CONSTANS_H
