#include "P3FissionEigenKernel.h"

registerMooseObject("ExampleApp", P3FissionEigenKernel);

template <>
InputParameters
validParams<P3FissionEigenKernel>()
{
  InputParameters params = validParams<EigenKernel>();
  params.addRequiredParam<unsigned int>("group_number", "The current energy group");
  params.addRequiredParam<unsigned int>("num_groups", "The total numer of energy groups");
  params.addRequiredCoupledVar("flux0_groups", "All the variables that hold the group fluxes 0. "
                                               "These MUST be listed by decreasing "
                                               "energy/increasing group number.");
  params.addRequiredCoupledVar("flux2_groups", "All the variables that hold the group fluxes 2. "
                                               "These MUST be listed by decreasing "
                                               "energy/increasing group number.");
  params.addParam<Real>("val1", 1.0, "Constant 1");
  params.addParam<Real>("val2", 1.0, "Constant 2");
  return params;
}

P3FissionEigenKernel::P3FissionEigenKernel(const InputParameters & parameters)
  : EigenKernel(parameters),
    _group(getParam<unsigned int>("group_number") - 1),
    _num_groups(getParam<unsigned int>("num_groups")),
    _nsf(getMaterialProperty<std::vector<Real>>("nsf")),
    _chi_t(getMaterialProperty<std::vector<Real>>("chi_t")),
    _val1(getParam<Real>("val1")),
    _val2(getParam<Real>("val2"))
{
  unsigned int n = coupledComponents("flux0_groups");
  // if (!(n == _num_groups))
  // {
  //   mooseError("The number of coupled variables doesn't match the number of groups.");
  // }
  _flux0_groups.resize(n);
  _flux0_ids.resize(n);
  _flux2_groups.resize(n);
  _flux2_ids.resize(n);

  for (unsigned int i = 0; i < _flux0_groups.size(); ++i)
  {
    _flux0_groups[i] = &coupledValue("flux0_groups", i);
    _flux0_ids[i] = coupled("flux0_groups", i);
    _flux2_groups[i] = &coupledValue("flux2_groups", i);
    _flux2_ids[i] = coupled("flux2_groups", i);
  }
}

Real
P3FissionEigenKernel::computeQpResidual()
{
  Real r = 0;
  for (unsigned int i = 0; i < _num_groups; ++i)
    r += _nsf[_qp][i] * (_val1 * (*_flux0_groups[i])[_qp] + _val2 * (*_flux2_groups[i])[_qp]);

  return -_test[_i][_qp] * _chi_t[_qp][_group] * r;
}

Real
P3FissionEigenKernel::computeQpJacobian()
{
  return -_test[_i][_qp] * _chi_t[_qp][_group] * _nsf[_qp][_i] * _val1 * _phi[_j][_qp];
}
