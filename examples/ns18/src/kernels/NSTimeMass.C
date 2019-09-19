#include "NSTimeMass.h"

registerMooseObject("ExampleApp", NSTimeMass);

template <>
InputParameters
validParams<NSTimeMass>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("This class computes the time derivative for the "
                             "mass equation.");
  //params.addRequiredCoupledVar("rho", "density");
  return params;
}

NSTimeMass::NSTimeMass(const InputParameters & parameters)
  : Kernel(parameters),
    _rho(*mooseVariable()),
    //_rho(coupledValue("rho")),
    _rho_dot(_rho.uDot())
{
}

Real
NSTimeMass::computeQpResidual()
{
  return _test[_i][_qp] * _rho_dot[_qp];
}

/*
Real
NSTimeMass::computeQpJacobian()
{
  return TimeDerivative::computeQpJacobian();
}

Real
NSTimeMass::computeQpOffDiagJacobian(unsigned)
{
  return 0.;
}
*/