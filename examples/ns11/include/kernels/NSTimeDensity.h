#ifndef NSTIMEDENSITY_H
#define NSTIMEDENSITY_H

#include "TimeDerivative.h"

// Forward Declarations
class NSTimeDensity;

template <>
InputParameters validParams<NSTimeDensity>();

class NSTimeDensity : public TimeDerivative
{
public:
  NSTimeDensity(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

};

#endif // NSTIMEDENSITY_H
