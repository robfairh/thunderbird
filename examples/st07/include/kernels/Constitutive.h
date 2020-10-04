#ifndef CONSTITUTIVE_H
#define CONSTITUTIVE_H

#include "Kernel.h"

class Constitutive;

template <>
InputParameters validParams<Constitutive>();

class Constitutive : public Kernel
{
public:
  Constitutive(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  const VariableValue & _sigma_x;

  const MaterialProperty<Real> & _E;
  const MaterialProperty<Real> & _nu;

};

#endif // CONSTITUTIVE_H
