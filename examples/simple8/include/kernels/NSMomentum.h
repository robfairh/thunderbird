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

  //const VariableValue & _rho;
  //const VariableGradient & _grad_rho;

  const VariableValue & _p;
  const VariableGradient & _grad_p;
  
  const MaterialProperty<Real> & _mu;
};

#endif
