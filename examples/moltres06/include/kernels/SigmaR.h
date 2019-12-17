#ifndef SIGMAR_H
#define SIGMAR_H

#include "Kernel.h"

class SigmaR;

template <>
InputParameters validParams<SigmaR>();

class SigmaR : public Kernel
{
public:
  SigmaR(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Real & _remxs;
};

#endif // SIGMAR_H