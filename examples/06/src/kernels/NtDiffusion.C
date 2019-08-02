#include "NtDiffusion.h"

registerMooseObject("ExampleApp", NtDiffusion);

template <>
InputParameters
validParams<NtDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addParam<Real>("diffcoef", 1.0, "Diffusion Coefficient");
  return params;
}

NtDiffusion::NtDiffusion(const InputParameters & parameters)
  : Diffusion(parameters),
    _diffcoef(getParam<Real>("diffcoef"))
{
}

Real
NtDiffusion::computeQpResidual()
{
  return _diffcoef * Diffusion::computeQpResidual();
}

Real
NtDiffusion::computeQpJacobian()
{
  return _diffcoef * Diffusion::computeQpJacobian();
}
