#ifndef SHEAR_X_H
#define SHEAR_X_H

#include "Kernel.h"

class Shear_x;

template <>
InputParameters validParams<Shear_x>();

class Shear_x : public Kernel
{
public:
  Shear_x(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  const VariableValue & _v_def;
  const VariableGradient & _grad_v_def;

  const MaterialProperty<Real> & _E;
  const MaterialProperty<Real> & _nu;

};

#endif // DEFORMATION_H
