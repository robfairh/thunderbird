#ifndef AUXCONSTITUTIVE_H
#define AUXCONSTITUTIVE_H

#include "AuxKernel.h"

class AuxConstitutive;

template <>
InputParameters validParams<AuxConstitutive>();

class AuxConstitutive : public AuxKernel
{
public:
  AuxConstitutive(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _u_def;
  const VariableGradient & _grad_u_def;
  const MaterialProperty<Real> & _E;

};

#endif // AUXCONSTITUTIVE_H
