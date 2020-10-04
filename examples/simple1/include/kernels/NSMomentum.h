#ifndef NSMOMENTUM_H
#define NSMOMENTUM_H

#include "Kernel.h"

class NSMomentum;

template <>
InputParameters validParams<Kernel>();

class NSMomentum : public Kernel
{
public:
  NSMomentum(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  
  // Material properties
  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _K;

};

#endif
