#include "P3Diffusion.h"

registerMooseObject("ExampleApp", P3Diffusion);

template <>
InputParameters
validParams<P3Diffusion>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("diffcoef", 1.0, "Diffusion Coefficient");
  return params;
}

P3Diffusion::P3Diffusion(const InputParameters & parameters)
  : Kernel(parameters),
    _diffcoef(getParam<Real>("diffcoef"))
{
}

Real
P3Diffusion::computeQpResidual()
{
  return _diffcoef * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real
P3Diffusion::computeQpJacobian()
{
  return _diffcoef * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}