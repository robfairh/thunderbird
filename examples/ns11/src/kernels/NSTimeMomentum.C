#include "NSTimeMomentum.h"

registerMooseObject("ExampleApp", NSTimeMomentum);

template <>
InputParameters
validParams<NSTimeMomentum>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addClassDescription("This class computes the time derivative for the "
                             "Navier-Stokes momentum equation.");
  params.addRequiredCoupledVar("rho", "density");
  return params;
}

NSTimeMomentum::NSTimeMomentum(const InputParameters & parameters)
  : TimeDerivative(parameters),
    _rho(coupledValue("rho")),
    _rho_var_number(coupled("rho"))
{
}

Real
NSTimeMomentum::computeQpResidual()
{
  return _rho[_qp] * TimeDerivative::computeQpResidual();
}

Real
NSTimeMomentum::computeQpJacobian()
{
  return _rho[_qp] * TimeDerivative::computeQpJacobian();
}

Real
NSTimeMomentum::computeQpOffDiagJacobian(unsigned jvar)
{
  Real jac = 0;
  if (jvar == _rho_var_number)
  {
    jac += _phi[_j][_qp] * TimeDerivative::computeQpResidual();
  }
  return jac;
}
