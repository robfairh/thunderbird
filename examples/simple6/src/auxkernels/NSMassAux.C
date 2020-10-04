#include "NSMassAux.h"

registerMooseObject("ExampleApp", NSMassAux);

template <>
InputParameters
validParams<NSMassAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("p", "pressure");
  params.addRequiredCoupledVar("temp", "temperature variable");

  params.addParam<Real>("p_ref", 1.0, "reference pressure");
  params.addParam<Real>("temp_ref", 1.0, "reference temperature");

  params.addParam<Real>("bulk_m", 1.0, "bulk modulus");
  params.addParam<Real>("beta", 1.0, "thermal expansion coefficient");
  
  params.addParam<Real>("rho_ref", 1.0, "reference density");
  return params;
}

NSMassAux::NSMassAux(const InputParameters & parameters)
  : AuxKernel(parameters),

    _p(coupledValue("p")),
    _temp(coupledValue("temp")),

    _p_ref(getParam<Real>("p_ref")),
    _temp_ref(getParam<Real>("temp_ref")),

    _bulk_m(getParam<Real>("bulk_m")),
    _beta(getParam<Real>("beta")),
    _rho_ref(getParam<Real>("rho_ref"))
{
}

Real
NSMassAux::computeValue()
{
  return _rho_ref + _rho_ref * _beta * (_temp[_qp]-_temp_ref) - _rho_ref/_bulk_m * (_p[_qp]-_p_ref);
}
