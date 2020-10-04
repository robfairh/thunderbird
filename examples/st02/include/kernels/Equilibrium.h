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

  const MaterialProperty<Real> & _rho;

};

#endif // EQUILIBRIUM_H
