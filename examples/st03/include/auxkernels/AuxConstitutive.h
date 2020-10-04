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

  const VariableValue & _sigma_x;
  const VariableValue & _sigma_y;
  unsigned _component;

  const Real & _E;
  //const MaterialProperty<Real> & _E;
  //const MaterialProperty<Real> & _nu;

};

#endif // AUXCONSTITUTIVE_H
