#include "ElmIntegTotFissNtsPostprocessor.h"

registerMooseObject("ExampleApp", ElmIntegTotFissNtsPostprocessor);

template <>
InputParameters
validParams<ElmIntegTotFissNtsPostprocessor>()
{
  InputParameters params = validParams<ElementIntegralPostprocessor>();
  params.addRequiredParam<unsigned int>("num_groups", "The total numer of energy groups");
  params.addRequiredCoupledVar("flux0_groups", "All the variables that hold the group fluxes 0. "
                                               "These MUST be listed by decreasing "
                                               "energy/increasing group number.");
  params.addRequiredCoupledVar("flux2_groups", "All the variables that hold the group fluxes 2. "
                                               "These MUST be listed by decreasing "
                                               "energy/increasing group number.");
  return params;
}

ElmIntegTotFissNtsPostprocessor::ElmIntegTotFissNtsPostprocessor(const InputParameters & parameters)
  : ElementIntegralPostprocessor(parameters),
    _num_groups(getParam<unsigned int>("num_groups")),
    _nsf(getMaterialProperty<std::vector<Real>>("nsf"))
    // _vars(getCoupledMooseVars())
{
  // addMooseVariableDependency(_vars);
  int n = coupledComponents("flux0_groups");
  // if (!(n == _num_groups))
  //   mooseError("The number of coupled variables doesn't match the number of groups.");

  _flux0_groups.resize(n);
  _flux2_groups.resize(n);

  for (unsigned int i = 0; i < _flux0_groups.size(); ++i)
  {
    _flux0_groups[i] = &coupledValue("flux0_groups", i);
    _flux2_groups[i] = &coupledValue("flux2_groups", i);
  }
}

Real
ElmIntegTotFissNtsPostprocessor::computeQpIntegral()
{

  Real sum = 0;
  for (unsigned int i = 0; i < _num_groups; ++i)
    sum += _nsf[_qp][i] * ((*_flux0_groups[i])[_qp] - 2. * (*_flux2_groups[i])[_qp]);

  return sum;
}
