#include "NSMass.h"

registerMooseObject("ExampleApp", NSMass);

template <>
InputParameters
validParams<NSMass>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("This class computes the mass equation residual and Jacobian "
                             "contributions for the Navier-Stokes momentum equation.");
  params.addRequiredCoupledVar("u", "x-velocity");
  params.addCoupledVar("v", 0, "y-velocity");
  params.addCoupledVar("w", 0, "z-velocity");
  params.addRequiredCoupledVar("rho", "density");
  return params;
}

NSMass::NSMass(const InputParameters & parameters)
  : Kernel(parameters),
    _u_vel(coupledValue("u")),
    _v_vel(coupledValue("v")),
    _w_vel(coupledValue("w")),
    _rho(coupledValue("rho")),
    _grad_u_vel(coupledGradient("u")),
    _grad_v_vel(coupledGradient("v")),
    _grad_w_vel(coupledGradient("w")),
    _grad_rho(coupledGradient("rho")),
    _u_vel_var_number(coupled("u")),
    _v_vel_var_number(coupled("v")),
    _w_vel_var_number(coupled("w")),
    _rho_var_number(coupled("rho"))
{
}

Real
NSMass::computeQpResidual()
{
  Real res = 0;
 
  res += _rho[_qp] * (_grad_u_vel[_qp](0) + _grad_v_vel[_qp](1) + _grad_w_vel[_qp](2)) * _test[_i][_qp];
  RealVectorValue U(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);
  res += _grad_rho[_qp] * U * _test[_i][_qp];
  
  return res;
}

/*
Real
NSMass::computeQpJacobian()
{
  Real r = 0;
  return r;
}

Real
NSMass::computeQpOffDiagJacobian(unsigned jvar)
{
  Real jac = 0;
  if (jvar == _u_vel_var_number)
  {
    jac += _rho[_qp] * _grad_phi[_j][_qp](0) * _test[_i][_qp];
    jac += _grad_rho[_qp](0) * _phi[_j][_qp] * _test[_i][_qp];
    return jac;
  }

  else if (jvar == _v_vel_var_number)
  {
    jac += _rho[_qp] * _grad_phi[_j][_qp](1) * _test[_i][_qp];
    jac += _grad_rho[_qp](1) * _phi[_j][_qp] * _test[_i][_qp];
    return jac;
  }

  else if (jvar == _w_vel_var_number)
  {
    jac += _rho[_qp] * _grad_phi[_j][_qp](1) * _test[_i][_qp];
    jac += _grad_rho[_qp](2) * _phi[_j][_qp] * _test[_i][_qp];
    return jac;
  }

  else if (jvar == _rho_var_number)
  {
    jac += _phi[_j][_qp] * (_grad_u_vel[_qp](0) + _grad_v_vel[_qp](1) + _grad_w_vel[_qp](2)) * _test[_i][_qp];
    RealVectorValue U(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);
    jac += _grad_phi[_j][_qp] * U * _test[_i][_qp];
    return jac;
  }

  else
    return 0.0;
}
*/