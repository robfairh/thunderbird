#include "NSMass.h"

registerMooseObject("ExampleApp", NSMass);

template <>
InputParameters
validParams<NSMass>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Mass equation");
  params.addRequiredCoupledVar("u", "x-velocity");
  return params;
}

NSMass::NSMass(const InputParameters & parameters)
  : Kernel(parameters),
    _u_vel(coupledValue("u")),
    _grad_u_vel(coupledGradient("u"))
{
}

Real
NSMass::computeQpResidual()
{
  Real res = 0;
  
  // Integral constraint
  //res += _u[_qp] * _u_vel[_qp] * _test[_i][_qp];
  //res += -_K[_qp] * _test[_i][_qp];
 
  // Differential constraint
  // res += _u_vel[_qp] * _grad_u[_qp](0) * _test[_i][_qp];
  //res += _u[_qp] * _grad_u_vel[_qp](0) * _test[_i][_qp];
  res += _grad_u_vel[_qp](0) * _test[_i][_qp];

  return res;
}
