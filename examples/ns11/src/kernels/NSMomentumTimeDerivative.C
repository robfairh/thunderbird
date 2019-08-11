#include "NSMomentumTimeDerivative.h"

registerMooseObject("ExampleApp", NSMomentumTimeDerivative);

template <>
InputParameters
validParams<NSMomentumTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addClassDescription("This class computes the time derivative for the "
                             "Navier-Stokes momentum equation.");
  params.addRequiredCoupledVar("rho", "density");
  return params;
}

NSMomentumTimeDerivative::NSMomentumTimeDerivative(const InputParameters & parameters)
  : TimeDerivative(parameters),
    _rho(coupledValue("rho")),
    _rho_var_number(coupled("rho"))
{
}

Real
NSMomentumTimeDerivative::computeQpResidual()
{
  return _rho[_qp] * TimeDerivative::computeQpResidual();
}

Real
NSMomentumTimeDerivative::computeQpJacobian()
{
  return _rho[_qp] * TimeDerivative::computeQpJacobian();
}

Real
NSMomentumTimeDerivative::computeQpOffDiagJacobian(unsigned jvar)
{
  if (jvar == _rho_var_number){
    //return _phi[_j][_qp] * TimeDerivative::computeQpResidual();
  }
  return 0.;
}
