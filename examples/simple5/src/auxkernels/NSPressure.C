#include "NSPressure.h"

registerMooseObject("ExampleApp", NSPressure);

template <>
InputParameters
validParams<NSPressure>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("rho", "Density");
  params.addRequiredCoupledVar("temp", "Temperature");
  //params.addParam<Real>("R", 1.0, "R for gas");
  return params;
}

NSPressure::NSPressure(const InputParameters & parameters)
  : AuxKernel(parameters),
    //_R(getParam<Real>("_R")),
    _rho(coupledValue("rho")),
    _temp(coupledValue("temp"))
{
}

Real
NSPressure::computeValue()
{
  return _rho[_qp] * 10. * _temp[_qp];
}
