#include "InScatter.h"

registerMooseObject("thunderbirdApp", InScatter);

template <>
InputParameters
validParams<InScatter>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("gtransfxs", 1.0, "Scattering Cross Section");
  params.addRequiredParam<unsigned int>("group_number", "The current energy group");
  params.addRequiredParam<unsigned int>("num_groups", "The total numer of energy groups");
  params.addRequiredCoupledVar("group_fluxes", "All the variables that hold the group fluxes. "
                                               "These MUST be listed by decreasing "
                                               "energy/increasing group number.");
  return params;
}

InScatter::InScatter(const InputParameters & parameters)
  : Kernel(parameters),
    _gtransfxs(getParam<Real>("gtransfxs")),
    _group(getParam<unsigned int>("group_number") - 1),
    _num_groups(getParam<unsigned int>("num_groups"))
{
  unsigned int n = coupledComponents("group_fluxes");
  if (!(n == _num_groups))
  {
    mooseError("The number of coupled variables doesn't match the number of groups.");
  }
  _group_fluxes.resize(n);
  _flux_ids.resize(n);
  for (unsigned int i = 0; i < _group_fluxes.size(); ++i)
  {
    _group_fluxes[i] = &coupledValue("group_fluxes", i);
    _flux_ids[i] = coupled("group_fluxes", i);
  }
}

Real
InScatter::computeQpResidual()
{
  Real r = 0;
  for (unsigned int i = 0; i < _num_groups; ++i)
  {
    if (i == _group)
      continue;
    r += -_test[_i][_qp] * _gtransfxs * (*_group_fluxes[i])[_qp];
  }
  return r;
}

Real
InScatter::computeQpJacobian()
{
  return 0.;
}
