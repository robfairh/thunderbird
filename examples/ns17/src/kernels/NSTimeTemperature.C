#include "NSTimeTemperature.h"

registerMooseObject("ExampleApp", NSTimeTemperature);

template <>
InputParameters
validParams<NSTimeTemperature>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addRequiredCoupledVar("rho", "density");
  return params;
}

NSTimeTemperature::NSTimeTemperature(const InputParameters & parameters)
  : DerivativeMaterialInterface<JvarMapKernelInterface<TimeDerivative>>(parameters),
    _rho(coupledValue("rho")),
    _rho_var_number(coupled("rho")),
    _cp(getMaterialProperty<Real>("cp")),
    _d_cp_d_u(getMaterialPropertyDerivative<Real>("cp", _var.name()))
{
}

void
NSTimeTemperature::initialSetup()
{
  validateNonlinearCoupling<Real>("cp");
}

Real
NSTimeTemperature::computeQpResidual()
{
  return _rho[_qp] * _cp[_qp] * TimeDerivative::computeQpResidual();
}
/*
Real
NSTimeTemperature::computeQpJacobian()
{
  return _rho[_qp] * _cp[_qp] * TimeDerivative::computeQpJacobian();
}

Real
NSTimeTemperature::computeQpOffDiagJacobian(unsigned jvar)
{
  if (jvar == _rho_var_number)
  {
    return _phi[_j][_qp] * _cp[_qp] * TimeDerivative::computeQpResidual();
  }
  else
    return 0;
}
*/
