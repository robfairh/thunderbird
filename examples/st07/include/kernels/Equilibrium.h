#ifndef EQUILIBRIUM_H
#define EQUILIBRIUM_H

#include "Kernel.h"

class Equilibrium;

template <>
InputParameters validParams<Equilibrium>();

class Equilibrium : public Kernel
{
public:
  Equilibrium(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  unsigned _component;
  const MaterialProperty<Real> & _rho;
  RealVectorValue _gravity;

};

#endif // EQUILIBRIUM_H
