#ifndef P3DIFFUSION_H
#define P3DIFFUSION_H

#include "Kernel.h"

class P3Diffusion;

template <>
InputParameters validParams<P3Diffusion>();

class P3Diffusion : public Kernel
{
public:
  P3Diffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Real & _diffcoef;
};

#endif // P3DIFFUSION_H
