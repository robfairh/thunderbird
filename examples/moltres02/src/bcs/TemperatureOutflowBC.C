#include "TemperatureOutflowBC.h"

registerMooseObject("ExampleApp", TemperatureOutflowBC);

template <>
InputParameters
validParams<TemperatureOutflowBC>()
{
  InputParameters params = validParams<OutflowBC>();
  params.addParam<Real>("rho", 1.0, "Density");
  params.addParam<Real>("cp", 1.0, "Heat Capacity");
  return params;
}

TemperatureOutflowBC::TemperatureOutflowBC(const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapIntegratedBCInterface<OutflowBC>>(parameters),
    _rho(getParam<Real>("rho")),
    _cp(getParam<Real>("cp"))
{
}

void
TemperatureOutflowBC::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
TemperatureOutflowBC::computeQpResidual()
{
  return _rho * _cp * OutflowBC::computeQpResidual();
}

Real
TemperatureOutflowBC::computeQpJacobian()
{
  return _rho * _cp * OutflowBC::computeQpJacobian();
}
