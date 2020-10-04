#ifndef COUPLEDFISSIONKERNEL_H
#define COUPLEDFISSIONKERNEL_H

#include "Kernel.h"

class CoupledFissionKernel;

template <>
InputParameters validParams<CoupledFissionKernel>();

class CoupledFissionKernel : public Kernel
{
public:
  CoupledFissionKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Real & _nfxs;
};

#endif // COUPLEDFISSIONKERNEL_H
