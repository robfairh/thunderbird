#include "ConservativeTemperatureAdvection.h"

registerMooseObject("ExampleApp", ConservativeTemperatureAdvection);

template <>
InputParameters
validParams<ConservativeTemperatureAdvection>()
{
  InputParameters params = validParams<ConservativeAdvection>();
  params.addParam<Real>("rho", 1.0, "Density");
  params.addParam<Real>("cp", 1.0, "Heat capacity");
  return params;
}

ConservativeTemperatureAdvection::ConservativeTemperatureAdvection(
    const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapKernelInterface<ConservativeAdvection>>(parameters),
    _rho(getParam<Real>("rho")),
    _cp(getParam<Real>("cp"))
{
}

void
ConservativeTemperatureAdvection::initialSetup()
{
  validateNonlinearCoupling<Real>("rho");
  validateNonlinearCoupling<Real>("cp");
}

Real
ConservativeTemperatureAdvection::computeQpResidual()
{
  return _rho * _cp * ConservativeAdvection::computeQpResidual();
}

Real
ConservativeTemperatureAdvection::computeQpJacobian()
{
  return _rho * _cp * ConservativeAdvection::computeQpJacobian();
}
