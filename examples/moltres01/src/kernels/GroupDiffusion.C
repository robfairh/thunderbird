#include "GroupDiffusion.h"

registerMooseObject("ExampleApp", GroupDiffusion);

template <>
InputParameters
validParams<GroupDiffusion>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("diffcoef", 1.0, "Diffusion Coefficient");
  params.addRequiredParam<unsigned int>("group_number",
                                        "The group for which this kernel controls diffusion");
  return params;
}

GroupDiffusion::GroupDiffusion(const InputParameters & parameters)
  : Kernel(parameters),
    _diffcoef(getParam<Real>("diffcoef")),
    _group(getParam<unsigned int>("group_number") - 1)
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