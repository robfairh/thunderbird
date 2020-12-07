#include "P3SigmaCoupled.h"

registerMooseObject("ExampleApp", P3SigmaCoupled);

template <>
InputParameters
validParams<P3SigmaCoupled>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<unsigned int>("group_number",
                                        "The group for which this kernel controls diffusion");
  params.addRequiredParam<unsigned int>("equation_number",
                                        "0 for equation A and 1 for equation B ");
  params.addRequiredCoupledVar("flux0_groups", "All the variables that hold the group fluxes 0. "
                                               "These MUST be listed by decreasing "
                                               "energy/increasing group number.");
  params.addRequiredCoupledVar("flux2_groups", "All the variables that hold the group fluxes 2. "
                                               "These MUST be listed by decreasing "
                                               "energy/increasing group number.");
  return params;
}

P3SigmaCoupled::P3SigmaCoupled(const InputParameters & parameters)
  : Kernel(parameters),
    _equation(getParam<unsigned int>("equation_number")),
    _group(getParam<unsigned int>("group_number") - 1),
    _couplexsA(getMaterialProperty<std::vector<Real>>("couplexsA")),
    _couplexsB(getMaterialProperty<std::vector<Real>>("couplexsB"))
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
P3SigmaCoupled::computeQpResidual()
{
  Real res = 0;

  if (_equation == 0)
      res = -_test[_i][_qp] * _couplexsA[_qp][_group] * (*_flux2_groups[_group])[_qp];
  else
      res = -_test[_i][_qp] * _couplexsB[_qp][_group] * (*_flux0_groups[_group])[_qp];

  return res;
}

Real
P3SigmaCoupled::computeQpJacobian()
{
  return 0.;
}
