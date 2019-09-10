#include "NSMomentum.h"

registerMooseObject("ExampleApp", NSMomentum);

template <>
InputParameters
validParams<NSMomentum>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Simple NS.");
  params.addRequiredCoupledVar("u", "x-velocity");
  params.addCoupledVar("v", 0, "y-velocity");
  params.addRequiredCoupledVar("rho", "density");
  params.addRequiredCoupledVar("p", "pressure");
  params.addParam<MaterialPropertyName>("mu_name", "mu", "Dynamic viscosity");
  params.addRequiredParam<unsigned>("component", "The velocity component that this is applied to.");
  return params;
}

NSMomentum::NSMomentum(const InputParameters & parameters)
  : Kernel(parameters),
    _u_vel(coupledValue("u")),
    _v_vel(coupledValue("v")),    
    _grad_u_vel(coupledGradient("u")),
    _grad_v_vel(coupledGradient("v")),
    _rho(coupledValue("rho")),
    _grad_rho(coupledGradient("rho")),
    _p(coupledValue("p")),
    _grad_p(coupledGradient("p")),
    _mu(getMaterialProperty<Real>("mu_name"))
{
}

Real
NSMomentum::computeQpResidual()
{
  Real r = 0;

  r += - _grad_p[_qp](0) * _test[_i][_qp];
  r += _mu[_qp] * (_grad_u[_qp] * _grad_test[_i][_qp]);

  RealVectorValue U(_u_vel[_qp], _v_vel[_qp]);
  RealVectorValue convec(U * _grad_u_vel[_qp], U * _grad_v_vel[_qp]);
  r += _test[_i][_qp] * _rho[_qp] * convec(_component);

  return r;
}
