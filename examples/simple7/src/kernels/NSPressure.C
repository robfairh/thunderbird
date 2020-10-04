#include "NSPressure.h"

registerMooseObject("ExampleApp", NSPressure);

template <>
InputParameters
validParams<NSPressure>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("rho", "Density");
  //params.addRequiredCoupledVar("temp", "Temperature");
  //params.addParam<Real>("R", 1.0, "R for gas");
  return params;
}

NSPressure::NSPressure(const InputParameters & parameters)
  : Kernel(parameters),
    //_R(getParam<Real>("_R")),
    _rho(coupledValue("rho"))
    //_temp(coupledValue("temp"))
{
}

Real
NSPressure::computeQpResidual()
{
//  return (_u[_qp]-_rho[_qp] * 10. * _temp[_qp]) * _test[_i][_qp];
  return (_u[_qp]-_rho[_qp] * 10.) * _test[_i][_qp];
}
