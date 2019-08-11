//* Viscous Dissipation Function Kernel

#include "NSTemperatureVD.h"

registerMooseObject("ExampleApp", NSTemperatureVD);

template <>
InputParameters
validParams<NSTemperatureVD>()
{
  InputParameters params = validParams<Kernel>();

  params.addClassDescription("This class computes the residual and Jacobian contributions for the "
                             "incompressible Navier-Stokes temperature (energy) equation.");
  // Coupled variables
  params.addRequiredCoupledVar("u", "x-velocity");
  params.addCoupledVar("v", 0, "y-velocity"); // only required in 2D and 3D
  params.addCoupledVar("w", 0, "z-velocity"); // only required in 3D

  // Optional parameters
  params.addParam<MaterialPropertyName>("rho_name", "rho", "density name");
  params.addParam<MaterialPropertyName>("k_name", "k", "thermal conductivity name");
  params.addParam<MaterialPropertyName>("cp_name", "cp", "specific heat name");
  params.addParam<MaterialPropertyName>("mu_name", "mu", "dynamic viscocity");

  return params;
}

NSTemperatureVD::NSTemperatureVD(const InputParameters & parameters)
  : Kernel(parameters),

    // Coupled variables
    _u_vel(coupledValue("u")),
    _v_vel(coupledValue("v")),
    _w_vel(coupledValue("w")),

    // Gradients
    _grad_u_vel(coupledGradient("u")),
    _grad_v_vel(coupledGradient("v")),
    _grad_w_vel(coupledGradient("w")),

    // Variable numberings
    _u_vel_var_number(coupled("u")),
    _v_vel_var_number(coupled("v")),
    _w_vel_var_number(coupled("w")),

    // Material Properties
    _rho(getMaterialProperty<Real>("rho_name")),
    _k(getMaterialProperty<Real>("k_name")),
    _cp(getMaterialProperty<Real>("cp_name")),
    _mu(getMaterialProperty<Real>("mu_name"))
{
}

Real
NSTemperatureVD::computeQpResidual()
{
  Real v_dissipation = 0;
  v_dissipation = -(2 * _mu[_qp] * _grad_u_vel[_qp](0) * _grad_u_vel[_qp](0) +
                  2 * _mu[_qp] * _grad_v_vel[_qp](1) * _grad_v_vel[_qp](1) +
                  2 * _mu[_qp] * _grad_w_vel[_qp](2) * _grad_w_vel[_qp](2) +
                  _mu[_qp] * (_grad_u_vel[_qp](1) + _grad_v_vel[_qp](0)) * (_grad_u_vel[_qp](1) + _grad_v_vel[_qp](0)) +
                  _mu[_qp] * (_grad_u_vel[_qp](2) + _grad_w_vel[_qp](0)) * (_grad_u_vel[_qp](2) + _grad_w_vel[_qp](0)) +
                  _mu[_qp] * (_grad_v_vel[_qp](2) + _grad_w_vel[_qp](1)) * (_grad_v_vel[_qp](2) + _grad_w_vel[_qp](1))) *
                  _test[_i][_qp];

  return v_dissipation;
}

Real
NSTemperatureVD::computeQpJacobian()
{
  Real jac = 0;

  return jac;
}

Real
NSTemperatureVD::computeQpOffDiagJacobian(unsigned jvar)
{
  if (jvar == _u_vel_var_number)
  {
    Real jac = 0;

    jac = -(2 * _mu[_qp] * _grad_phi[_j][_qp](0) * _grad_u_vel[_qp](0) +
           2 * _mu[_qp] * _grad_u_vel[_qp](0) * _grad_phi[_j][_qp](0) +
           _mu[_qp] * (_grad_phi[_j][_qp](1) + _grad_v_vel[_qp](0)) * (_grad_u_vel[_qp](1) + _grad_v_vel[_qp](0)) +
           _mu[_qp] * (_grad_u_vel[_qp](1) + _grad_v_vel[_qp](0)) * (_grad_phi[_j][_qp](1) + _grad_v_vel[_qp](0)) +          
           _mu[_qp] * (_grad_phi[_j][_qp](2) + _grad_w_vel[_qp](0)) * (_grad_u_vel[_qp](2) + _grad_w_vel[_qp](0)) +
           _mu[_qp] * (_grad_u_vel[_qp](1) + _grad_w_vel[_qp](0)) * (_grad_phi[_j][_qp](2) + _grad_w_vel[_qp](0))) *
           _test[_i][_qp];

    return jac;
  }

  else if (jvar == _v_vel_var_number)
  {
    Real jac = 0;

    jac = -(2 * _mu[_qp] * _grad_phi[_j][_qp](1) * _grad_v_vel[_qp](1) +
           2 * _mu[_qp] * _grad_u_vel[_qp](1) * _grad_phi[_j][_qp](1) +
           _mu[_qp] * (_grad_u_vel[_qp](1) + _grad_phi[_j][_qp](0)) * (_grad_u_vel[_qp](1) + _grad_v_vel[_qp](0)) +
           _mu[_qp] * (_grad_u_vel[_qp](1) + _grad_v_vel[_qp](0)) * (_grad_u_vel[_qp](1) + _grad_phi[_j][_qp](0)) +          
           _mu[_qp] * (_grad_phi[_j][_qp](2) + _grad_w_vel[_qp](1)) * (_grad_v_vel[_qp](2) + _grad_w_vel[_qp](1)) +
           _mu[_qp] * (_grad_v_vel[_qp](2) + _grad_w_vel[_qp](1)) * (_grad_phi[_j][_qp](2) + _grad_w_vel[_qp](1))) *
           _test[_i][_qp];

    return jac;
  }

  else if (jvar == _w_vel_var_number)
  {
    Real jac = 0;

    jac = -(2 * _mu[_qp] * _grad_phi[_j][_qp](2) * _grad_w_vel[_qp](2) +
           2 * _mu[_qp] * _grad_w_vel[_qp](2) * _grad_phi[_j][_qp](2) +
           _mu[_qp] * (_grad_u_vel[_qp](2) + _grad_phi[_j][_qp](0)) * (_grad_u_vel[_qp](2) + _grad_w_vel[_qp](0)) +
           _mu[_qp] * (_grad_u_vel[_qp](2) + _grad_w_vel[_qp](0)) * (_grad_u_vel[_qp](2) + _grad_phi[_j][_qp](0)) +          
           _mu[_qp] * (_grad_v_vel[_qp](2) + _grad_phi[_j][_qp](1)) * (_grad_v_vel[_qp](2) + _grad_w_vel[_qp](1)) +
           _mu[_qp] * (_grad_v_vel[_qp](2) + _grad_w_vel[_qp](1)) * (_grad_v_vel[_qp](2) + _grad_phi[_j][_qp](1))) *
           _test[_i][_qp];

    return jac;
  }
  else
    return 0;
}