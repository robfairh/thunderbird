#include "TempConvection.h"

registerMooseObject("ExampleApp", TempConvection);

template <>
InputParameters
validParams<TempConvection>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<RealVectorValue>("velocity", "Velocity Vector");
  params.addParam<Real>("rho", 1.0, "Density");
  params.addParam<Real>("cp", 1.0, "Heat capacity");
  return params;
}

TempConvection::TempConvection(const InputParameters & parameters)
  : Kernel(parameters),
    _velocity(getParam<RealVectorValue>("velocity")),
    _rho(getParam<Real>("rho")),
    _cp(getParam<Real>("cp"))
{
}

Real
TempConvection::computeQpResidual()
{
  return _rho * _cp * _test[_i][_qp] * (_velocity * _grad_u[_qp]);
}

Real
TempConvection::computeQpJacobian()
{
  return _rho * _cp * _test[_i][_qp] * (_velocity * _grad_phi[_j][_qp]);
}
