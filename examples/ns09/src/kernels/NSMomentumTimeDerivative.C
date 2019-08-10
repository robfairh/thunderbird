#include "NSMomentumTimeDerivative.h"

registerMooseObject("ExampleApp", NSMomentumTimeDerivative);

template <>
InputParameters
validParams<NSMomentumTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addClassDescription("This class computes the time derivative for the "
                             "Navier-Stokes momentum equation.");
  params.addParam<MaterialPropertyName>("rho_name", "rho", "density name");
  return params;
}

NSMomentumTimeDerivative::NSMomentumTimeDerivative(const InputParameters & parameters)
  : TimeDerivative(parameters), _rho(getMaterialProperty<Real>("rho_name"))
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
NSMomentumTimeDerivative::computeQpOffDiagJacobian(unsigned)
{
  return 0.;
}
