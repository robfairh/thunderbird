#include "TempDiffusion.h"

registerMooseObject("ExampleApp", TempDiffusion);

template <>
InputParameters
validParams<TempDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addParam<Real>("tempdiffcoef", 1.0, "Thermal conductivity");
  return params;
}

TempDiffusion::TempDiffusion(const InputParameters & parameters)
  : Diffusion(parameters),
    _tempdiffcoef(getParam<Real>("tempdiffcoef"))
{
}

Real
TempDiffusion::computeQpResidual()
{
  return _tempdiffcoef * Diffusion::computeQpResidual();
}

Real
TempDiffusion::computeQpJacobian()
{
  return _tempdiffcoef * Diffusion::computeQpJacobian();
}
