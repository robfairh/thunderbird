#ifndef AUXSHEAR_H
#define AUXSHEAR_H

#include "AuxKernel.h"

class AuxShear;

template <>
InputParameters validParams<AuxShear>();

class AuxShear : public AuxKernel
{
public:
  AuxShear(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _u_def;
  const VariableValue & _v_def;
  const VariableGradient & _grad_u_def;
  const VariableGradient & _grad_v_def;

  const Real & _E;
  const Real & _nu;

};

#endif // AUXSHEAR_H
