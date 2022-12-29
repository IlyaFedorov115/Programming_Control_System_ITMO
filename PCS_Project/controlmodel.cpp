#include "controlmodel.h"
#include "lintegrator.h"
#include "blocks/gain/gain.h"

/** setting integrators from left to right
    gains set from first = by init state to second = result state
*/
ControlModel::ControlModel(QVector<double>& states, QVector<QPair<double, double>>& gains,
                           QPair<double, double>& sigGain)
{
    if (states.size() == 0 || states.size() != gains.size())
        throw ControlModelError();

    for (auto state : states){
        integrators_.push_back(new LIntegrator(state));
    }

    for (auto currgain: gains){
        gains_.push_back(QPair<Gain*, Gain*>(
                             new Gain(currgain.first), new Gain(currgain.second)));
    }

    this->inputSignalGain_.first = new Gain(sigGain.first);
    this->inputSignalGain_.second = new Gain(sigGain.second);
}

double ControlModel::update(double inputVal, double dt)
{
    double currStates[integrators_.size()];

    for (int i = integrators_.size()-1; i >= 0; i--)
    {
        currStates[i] = gains_[i].first->update(integrators_[i]->getState());
    }

    double currInput = inputSignalGain_.first->update(inputVal);

    /** init for result summ  */
    double currInputIntegrator = currInput;
    for (int i = 0; i < integrators_.size(); i++){
        currInputIntegrator += currStates[i];
    }


    for (int i = 0; i < integrators_.size(); i++){
        currInputIntegrator = integrators_[i]->update(currInputIntegrator, dt);
    }

    /** get result summ */
    currInput = inputSignalGain_.second->update(currInput);
    for (int i = 0; i < integrators_.size(); i++){
        currInput += gains_[i].second->update(integrators_[i]->getState());
    }

    return currInput;
}





