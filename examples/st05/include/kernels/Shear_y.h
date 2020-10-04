#ifndef SHEAR_Y_H
#define SHEAR_Y_H

#include "Kernel.h"

class Shear_y;

template <>
InputParameters validParams<Shear_y>();

class Shear_y : public Kernel
{
public:
  Shear_y(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  const VariableValue & _v_def;
  const VariableGradient & _grad_v_def;

  const MaterialProperty<Real> & _E;
  const MaterialProperty<Real> & _nu;

};

#endif // DEFORMATION_H
