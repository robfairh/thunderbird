#ifndef TEMPDIFFUSION_H
#define TEMPDIFFUSION_H

#include "Diffusion.h"

// Forward Declaration
class TempDiffusion;

template <>
InputParameters validParams<TempDiffusion>();

class TempDiffusion : public Diffusion
{
public:
  TempDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _diffcoef;
};

#endif // TEMPDIFFUSION_H