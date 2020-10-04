#ifndef EQUILIBRIUM2_H
#define EQUILIBRIUM2_H

#include "Kernel.h"

class Equilibrium2;

template <>
InputParameters validParams<Equilibrium2>();

class Equilibrium2 : public Kernel
{
public:
  Equilibrium2(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  unsigned _component;
  const MaterialProperty<Real> & _rho;
  RealVectorValue _gravity;

};

#endif // EQUILIBRIUM2_H
