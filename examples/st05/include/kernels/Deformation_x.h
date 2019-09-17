#ifndef DEFORMATION_X_H
#define DEFORMATION_X_H

#include "Kernel.h"

class Deformation_x;

template <>
InputParameters validParams<Deformation_x>();

class Deformation_x : public Kernel
{
public:
  Deformation_x(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  const VariableValue & _v_def;
  const VariableGradient & _grad_v_def;

  const MaterialProperty<Real> & _E;
  const MaterialProperty<Real> & _nu;

};

#endif // DEFORMATION_H
