#ifndef NSTIMEMASS_H
#define NSTIMEMASS_H

#include "TimeDerivative.h"

// Forward Declarations
class NSTimeMass;

template <>
InputParameters validParams<NSTimeMass>();

class NSTimeMass : public TimeDerivative
{
public:
  NSTimeMass(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  //virtual Real computeQpJacobian();
  //virtual Real computeQpOffDiagJacobian(unsigned jvar);

};

#endif // NSTIMEMASS_H
