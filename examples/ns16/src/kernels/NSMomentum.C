#include "NSMomentum.h"

registerMooseObject("ExampleApp", NSMomentum);

template <>
InputParameters
validParams<NSMomentum>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("This class computes momentum equation residual and Jacobian viscous "
                             "contributions for the 'Laplacian' form of the governing equations.");
  params.addRequiredCoupledVar("u", "x-velocity");
  params.addCoupledVar("v", 0, "y-velocity");
  params.addCoupledVar("w", 0, "z-velocity");
  params.addRequiredCoupledVar("rho", "density");
  params.addRequiredCoupledVar("temp", "temperature");
  params.addRequiredParam<unsigned>("component", "The velocity component that this is applied to.");
  params.addParam<MaterialPropertyName>("mu_name", "mu", "Dynamic viscosity");
  params.addParam<MaterialPropertyName>("R_name", "R", "Gases constant");
  params.addParam<RealVectorValue>("gravity", RealVectorValue(0, 0, 0), "Gravity vector");
  return params;
}

NSMomentum::NSMomentum(const InputParameters & parameters)
  : Kernel(parameters),
    
    _u_vel(coupledValue("u")),
    _v_vel(coupledValue("v")),
    _w_vel(coupledValue("w")),
    _rho(coupledValue("rho")),
    _temp(coupledValue("temp")),
    
    _grad_u_vel(coupledGradient("u")),
    _grad_v_vel(coupledGradient("v")),
    _grad_w_vel(coupledGradient("w")),
    _grad_rho(coupledGradient("rho")),
    _grad_temp(coupledGradient("temp")),

    _u_vel_var_number(coupled("u")),
    _v_vel_var_number(coupled("v")),
    _w_vel_var_number(coupled("w")),
    _rho_var_number(coupled("rho")),
    _temp_var_number(coupled("temp")),

    _component(getParam<unsigned>("component")),
    _mu(getMaterialProperty<Real>("mu_name")),
    _R(getMaterialProperty<Real>("R_name")),
    _gravity(getParam<RealVectorValue>("gravity"))
{
}

Real
NSMomentum::computeQpResidual()
{
  Real r = 0;
  // viscous term
  r += _mu[_qp] * (_grad_u[_qp] * _grad_test[_i][_qp]);
  // pressure term
  r += _test[_i][_qp] * _rho[_qp] * _R[_qp] * _grad_temp[_qp](_component);
  r += _test[_i][_qp] * _temp[_qp] * _R[_qp] * _grad_rho[_qp](_component);
  // body force term
  r += -_test[_i][_qp] * _rho[_qp] * _gravity(_component);
  // convective term
  RealVectorValue U(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);
  RealVectorValue convec(U * _grad_u_vel[_qp], U * _grad_v_vel[_qp], U * _grad_w_vel[_qp]);
  r += _test[_i][_qp] * _rho[_qp] * convec(_component);

  return r;
}

Real
NSMomentum::computeQpJacobian()
{
  Real jac = 0;
  // viscous term
  jac += _mu[_qp] * (_grad_phi[_j][_qp] * _grad_test[_i][_qp]);
  // convective term
  jac += _test[_i][_qp] * dConvecDUComp(_component)(_component);

  return jac;
}

Real
NSMomentum::computeQpOffDiagJacobian(unsigned jvar)
{
  Real jac = 0;
  if (jvar == _u_vel_var_number)
  {
    // viscous term
    jac += 0.;
    // convective term
    jac += _test[_i][_qp] * dConvecDUComp(0)(_component);

    return jac;
  }
  else if (jvar == _v_vel_var_number)
  {
    // viscous term
    jac += 0.;
    // convective term
    jac += _test[_i][_qp] * dConvecDUComp(1)(_component);

    return jac;
  }
  else if (jvar == _w_vel_var_number)
  {
    // viscous term
    jac += 0.;
    // convective term
    jac += _test[_i][_qp] * dConvecDUComp(2)(_component);

    return jac;
  }
 
  if (jvar == _rho_var_number)
  {
    jac += 0;

    return jac;
  }

  if (jvar == _temp_var_number)
  {
    jac += 0;

    return jac;
  }

  else
    return 0;
}

RealVectorValue
NSMomentum::dConvecDUComp(unsigned comp)
{
  RealVectorValue U(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);
  RealVectorValue d_U_d_comp(0, 0, 0);
  d_U_d_comp(comp) = _phi[_j][_qp];

  RealVectorValue convective_term = _rho[_qp] * RealVectorValue(d_U_d_comp * _grad_u_vel[_qp],
                                                                d_U_d_comp * _grad_v_vel[_qp],
                                                                d_U_d_comp * _grad_w_vel[_qp]);
  convective_term(comp) += _rho[_qp] * U * _grad_phi[_j][_qp];

  return convective_term;
}