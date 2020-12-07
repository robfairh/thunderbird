#include "P3Diffusion.h"

registerMooseObject("ExampleApp", P3Diffusion);

template <>
InputParameters
validParams<P3Diffusion>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<unsigned int>("group_number",
                                        "The group for which this kernel controls diffusion");
  params.addRequiredParam<unsigned int>("equation_number",
                                        "0 for equation A and 1 for equation B ");
  return params;
}

P3Diffusion::P3Diffusion(const InputParameters & parameters)
  : Kernel(parameters),
    _equation(getParam<unsigned int>("equation_number")),
    _group(getParam<unsigned int>("group_number") - 1),
    _diffcoefA(getMaterialProperty<std::vector<Real>>("diffcoefA")),
    _d_diffcoefA_d_temp(getMaterialProperty<std::vector<Real>>("d_diffcoefA_d_temp")),
    _diffcoefB(getMaterialProperty<std::vector<Real>>("diffcoefB")),
    _d_diffcoefB_d_temp(getMaterialProperty<std::vector<Real>>("d_diffcoefB_d_temp"))
{
}

Real
P3Diffusion::computeQpResidual()
{
  Real res = 0;

  if (_equation == 0)
      res = _diffcoefA[_qp][_group] * _grad_test[_i][_qp] * _grad_u[_qp];
  else
      res = _diffcoefB[_qp][_group] * _grad_test[_i][_qp] * _grad_u[_qp];

  return res;
}

Real
P3Diffusion::computeQpJacobian()
{
    Real jac = 0;

    if (_equation == 0)
        jac = _diffcoefA[_qp][_group] * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
    else
        jac = _diffcoefB[_qp][_group] * _grad_test[_i][_qp] * _grad_phi[_j][_qp];

    return jac;
}

Real
P3Diffusion::computeQpOffDiagJacobian()
{
  return 0;
}