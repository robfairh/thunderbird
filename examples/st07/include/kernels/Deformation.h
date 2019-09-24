#ifndef DEFORMATION_H
#define DEFORMATION_H

#include "Kernel.h"

class Deformation;

template <>
InputParameters validParams<Deformation>();

class Deformation : public Kernel
{
public:
  Deformation(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  const VariableValue & _strain_x;
  const VariableValue & _strain_y;

  unsigned _component;

};

#endif // DEFORMATION_H
