#include "GroupDiffusion.h"

registerMooseObject("ExampleApp", GroupDiffusion);

template <>
InputParameters
validParams<GroupDiffusion>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<unsigned int>("group_number",
                                        "The group for which this kernel controls diffusion");
  params.addCoupledVar("temperature",
                       "The temperature used to interpolate the diffusion coefficient");
  return params;
}

GroupDiffusion::GroupDiffusion(const InputParameters & parameters)
  : Kernel(parameters),
    _diffcoef(getMaterialProperty<std::vector<Real>>("diffcoef")),
    _d_diffcoef_d_temp(getMaterialProperty<std::vector<Real>>("d_diffcoef_d_temp")),
    _group(getParam<unsigned int>("group_number") - 1),
    _temp_id(coupled("temperature"))
{
}

Real
GroupDiffusion::computeQpResidual()
{
  //return _diffcoef[_qp][_group] * _grad_test[_i][_qp] * computeConcentrationGradient(_u, _grad_u, _qp);
  return _diffcoef[_qp][_group] * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real
GroupDiffusion::computeQpJacobian()
{
  //return _diffcoef[_qp][_group] * _grad_test[_i][_qp] * computeConcentrationGradientDerivative(_u, _grad_u, _phi, _grad_phi, _j, _qp);
  return _diffcoef[_qp][_group] * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
}
