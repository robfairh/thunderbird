#include "ElmIntegTotFissNtsPostprocessor.h"

registerMooseObject("ExampleApp", ElmIntegTotFissNtsPostprocessor);

template <>
InputParameters
validParams<ElmIntegTotFissNtsPostprocessor>()
{
  InputParameters params = validParams<ElementIntegralPostprocessor>();
  params.addRequiredCoupledVar("first_flux", "flux 1.");
  params.addRequiredCoupledVar("second_flux", "flux 2.");
  params.addParam<Real>("nsf", 1.0, "nu sigma f");
  return params;
}

ElmIntegTotFissNtsPostprocessor::ElmIntegTotFissNtsPostprocessor(const InputParameters & parameters)
  : ElementIntegralPostprocessor(parameters),
    _first_flux(coupledValue("first_flux")),
    _second_flux(coupledValue("second_flux")),
    _nsf(getParam<Real>("nsf"))
{
}

Real
ElmIntegTotFissNtsPostprocessor::computeQpIntegral()
{ 
  return _nsf * (_first_flux[_qp] - 2 * _second_flux[_qp]);
}
