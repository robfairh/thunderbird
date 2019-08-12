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
  params.addRequiredCoupledVar("p", "pressure");
  params.addRequiredCoupledVar("rho", "density");
  params.addRequiredParam<unsigned>("component", "The velocity component that this is applied to.");
  params.addParam<MaterialPropertyName>("mu_name", "mu", "Dynamic viscosity");
  params.addParam<RealVectorValue>("gravity", RealVectorValue(0, 0, 0), "Gravity vector");
  return params;
}

NSMomentum::NSMomentum(const InputParameters & parameters)
  : Kernel(parameters),
    
    _u_vel(coupledValue("u")),
    _v_vel(coupledValue("v")),
    _w_vel(coupledValue("w")),
    _p(coupledValue("p")),
    _rho(coupledValue("rho")),
    
    _grad_u_vel(coupledGradient("u")),
    _grad_v_vel(coupledGradient("v")),
    _grad_w_vel(coupledGradient("w")),
    _grad_p(coupledGradient("p")),

    _u_vel_var_number(coupled("u")),
    _v_vel_var_number(coupled("v")),
    _w_vel_var_number(coupled("w")),
    _p_var_number(coupled("p")),
    _rho_var_number(coupled("rho")),

    _component(getParam<unsigned>("component")),
    _mu(getMaterialProperty<Real>("mu_name")),
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
  r += _test[_i][_qp] * _grad_p[_qp](_component);
  // body force term
  r += -_test[_i][_qp] * _rho[_qp] * _gravity(_component);
  // convective term
  RealVectorValue U(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);
  RealVectorValue convec(U * _grad_u_vel[_qp], U * _grad_v_vel[_qp], U * _grad_w_vel[_qp]);
  r += _test[_i][_qp] * _rho[_qp] * convec(_component);
  
  // viscous term from compressible flow
  r += 1/3 * _mu[_qp] * (_grad_u_vel[_qp](0) + _grad_v_vel[_qp](1) + _grad_w_vel[_qp](2)) * _grad_test[_i][_qp](_component);
  // missing BCs
  
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

  // viscous term from compressible flow
  jac += 1/3 * _mu[_qp] * _grad_phi[_j][_qp](_component) * _grad_test[_i][_qp](_component);

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
  else if (jvar == _p_var_number)
  {
    jac += _test[_i][_qp] * _grad_phi[_j][_qp](_component);

    return jac;
  }
  else if (jvar == _rho_var_number)
  {
    //This should add all the terms that have rho
    // viscous term
    jac += 0.;
    // body force term
    jac += -_test[_i][_qp] * _phi[_j][_qp] * _gravity(_component);
    // convective term
    RealVectorValue U(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);
    RealVectorValue convec(U * _grad_u_vel[_qp], U * _grad_v_vel[_qp], U * _grad_w_vel[_qp]);
    jac += _test[_i][_qp] * _phi[_j][_qp] * convec(_component);

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