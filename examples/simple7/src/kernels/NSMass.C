#include "NSMass.h"

registerMooseObject("ExampleApp", NSMass);

template <>
InputParameters
validParams<NSMass>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Mass equation");
  params.addRequiredCoupledVar("u", "x-velocity");
  params.addCoupledVar("v", 0, "y-velocity");
  return params;
}

NSMass::NSMass(const InputParameters & parameters)
  : Kernel(parameters),
    _u_vel(coupledValue("u")),
    _v_vel(coupledValue("v")),
    _grad_u_vel(coupledGradient("u")),
    _grad_v_vel(coupledGradient("v"))
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
  res += _u_vel[_qp] * _grad_u[_qp](0) * _test[_i][_qp];
  res += _v_vel[_qp] * _grad_u[_qp](1) * _test[_i][_qp];

  res += _u[_qp] * _grad_u_vel[_qp](0) * _test[_i][_qp];
  res += _u[_qp] * _grad_v_vel[_qp](1) * _test[_i][_qp];

  return res;
}
