#include "TempDiffusion.h"

registerMooseObject("ExampleApp", TempDiffusion);

template <>
InputParameters
validParams<TempDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  return params;
}

TempDiffusion::TempDiffusion(const InputParameters & parameters)
  : Diffusion(parameters),
    _diffusivity(getMaterialProperty<Real>("diffusivity"))
{
}

Real
TempDiffusion::computeQpResidual()
{
  return _diffusivity[_qp] * Diffusion::computeQpResidual();
}

Real
TempDiffusion::computeQpJacobian()
{
  return _diffusivity[_qp] * Diffusion::computeQpJacobian();
}
