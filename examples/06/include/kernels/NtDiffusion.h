#ifndef NTDIFFUSION_H
#define NTDIFFUSION_H

#include "Diffusion.h"

// Forward Declaration
class NtDiffusion;

template <>
InputParameters validParams<NtDiffusion>();

class NtDiffusion : public Diffusion
{
public:
  NtDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _diffcoef;
};

#endif // NTDIFFUSION_H