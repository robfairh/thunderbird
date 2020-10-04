#ifndef CONSTI_H
#define CONSTI_H

#include "Kernel.h"

class Consti;

template <>
InputParameters validParams<Consti>();

class Consti : public Kernel
{
public:
  Consti(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  const VariableValue & _u_def;
  const VariableGradient & _grad_u_def;
  const MaterialProperty<Real> & _E;

};

#endif // CONSTI_H
