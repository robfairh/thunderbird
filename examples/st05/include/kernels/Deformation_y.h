#ifndef DEFORMATION_Y_H
#define DEFORMATION_Y_H

#include "Kernel.h"

class Deformation_y;

template <>
InputParameters validParams<Deformation_y>();

class Deformation_y : public Kernel
{
public:
  Deformation_y(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  const VariableValue & _u_def;
  const VariableGradient & _grad_u_def;
  const MaterialProperty<Real> & _E;
  const MaterialProperty<Real> & _nu;

};

#endif // DEFORMATION_H
