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
  virtual Real computeQpOffDiagJacobian();

  bool _equation;
  unsigned int _group;
  const MaterialProperty<std::vector<Real>> & _diffcoefA;
  const MaterialProperty<std::vector<Real>> & _d_diffcoefA_d_temp;
  const MaterialProperty<std::vector<Real>> & _diffcoefB;
  const MaterialProperty<std::vector<Real>> & _d_diffcoefB_d_temp;
};

#endif // P3DIFFUSION_H
