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

  const MaterialProperty<Real> & _E;
  const MaterialProperty<Real> & _nu;

};

#endif // DEFORMATION_H
