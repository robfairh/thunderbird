#include "P3VacuumBC.h"

registerMooseObject("ExampleApp", P3VacuumBC);

template <>
InputParameters
validParams<P3VacuumBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("second_flux", "Second flux");
  params.addParam<Real>("val1", 1.0, "first constant");
  params.addParam<Real>("val2", 1.0, "second constant");
  return params;
}

P3VacuumBC::P3VacuumBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _second_flux(coupledValue("second_flux")),
    _val1(getParam<Real>("val1")),
    _val2(getParam<Real>("val2"))
{
}

Real
P3VacuumBC::computeQpResidual()
{
  // return _test[_i][_qp] * (_val1 * _u[_qp] + _val2 * _second_flux[_qp]);
  return _test[_i][_qp] * (_val1 * _u[_qp] + _val2 * _second_flux[_qp]);
}

Real
P3VacuumBC::computeQpJacobian()
{
  return _test[_i][_qp] * _val1 * _phi[_j][_qp];
}
