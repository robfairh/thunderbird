#ifndef NSMASS_H
#define NSMASS_H

#include "Kernel.h"

class NSMass;

template <>
InputParameters validParams<NSMass>();

class NSMass : public Kernel
{
public:
  NSMass(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  const VariableValue & _u_vel;
  const VariableGradient & _grad_u_vel;

  const MaterialProperty<Real> & _K;

};

#endif // NSMASS_H
