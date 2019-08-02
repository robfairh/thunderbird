#include "TempDiffusion.h"

registerMooseObject("ExampleApp", TempDiffusion);

template <>
InputParameters
validParams<TempDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addParam<Real>("diffcoef", 1.0, "Diffusion Coefficient");
  return params;
}

TempDiffusion::TempDiffusion(const InputParameters & parameters)
  : Diffusion(parameters),
    _diffcoef(getParam<Real>("diffcoef"))
{
}

Real
TempDiffusion::computeQpResidual()
{
  return _diffcoef * Diffusion::computeQpResidual();
}

Real
TempDiffusion::computeQpJacobian()
{
  return _diffcoef * Diffusion::computeQpJacobian();
}
