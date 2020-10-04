#include "GroupDiffusion.h"

registerMooseObject("ExampleApp", GroupDiffusion);

template <>
InputParameters
validParams<GroupDiffusion>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("diffcoef", 1.0, "Diffusion Coefficient");
  return params;
}

GroupDiffusion::GroupDiffusion(const InputParameters & parameters)
  : Kernel(parameters),
    _diffcoef(getParam<Real>("diffcoef"))
{
}

Real
GroupDiffusion::computeQpResidual()
{
  return _diffcoef * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real
GroupDiffusion::computeQpJacobian()
{
  return _diffcoef * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}