#include "NSTemperature.h"

registerMooseObject("ExampleApp", NSTemperature);

template <>
InputParameters
validParams<NSTemperature>()
{
  InputParameters params = validParams<Kernel>();

  params.addClassDescription("This class computes the residual and Jacobian contributions for the "
                             "incompressible Navier-Stokes temperature (energy) equation.");
  // Coupled variables
  params.addRequiredCoupledVar("u", "x-velocity");
  params.addCoupledVar("v", 0, "y-velocity"); // only required in 2D and 3D
  params.addCoupledVar("w", 0, "z-velocity"); // only required in 3D
  params.addRequiredCoupledVar("p", "pressure");
  params.addRequiredCoupledVar("rho", "density");

  // Optional parameters
  params.addParam<MaterialPropertyName>("k_name", "k", "thermal conductivity name");
  params.addParam<MaterialPropertyName>("cp_name", "cp", "specific heat name");

  return params;
}

NSTemperature::NSTemperature(const InputParameters & parameters)
  : Kernel(parameters),

    // Coupled variables
    _u_vel(coupledValue("u")),
    _v_vel(coupledValue("v")),
    _w_vel(coupledValue("w")),
    _p(coupledValue("p")),
    _rho(coupledValue("rho")),

    _grad_u_vel(coupledGradient("u")),
    _grad_v_vel(coupledGradient("v")),
    _grad_w_vel(coupledGradient("w")),

    // Variable numberings
    _u_vel_var_number(coupled("u")),
    _v_vel_var_number(coupled("v")),
    _w_vel_var_number(coupled("w")),
    _p_var_number(coupled("p")),
    _rho_var_number(coupled("rho")),

    // Material Properties
    _k(getMaterialProperty<Real>("k_name")),
    _cp(getMaterialProperty<Real>("cp_name"))
{
}

Real
NSTemperature::computeQpResidual()
{
  // Note: _u is the temperature variable, _grad_u is its gradient.
  Real convective_part = _rho[_qp] * _cp[_qp] *
                         (_u_vel[_qp] * _grad_u[_qp](0) + _v_vel[_qp] * _grad_u[_qp](1) +
                          _w_vel[_qp] * _grad_u[_qp](2)) *
                         _test[_i][_qp];

  // Thermal conduction part, k * grad(T) * grad(v)
  Real conduction_part = _k[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];

  // Compressible flow
  //Real compress_part = _p[_qp] * (_grad_u_vel[_qp](0) + _grad_v_vel[_qp](1) + _grad_w_vel[_qp](2));

  //return convective_part + conduction_part + compress_part;
  return convective_part + conduction_part;
}

Real
NSTemperature::computeQpJacobian()
{
  RealVectorValue U(_u_vel[_qp], _v_vel[_qp], _w_vel[_qp]);

  Real convective_part = _rho[_qp] * _cp[_qp] * (U * _grad_phi[_j][_qp]) * _test[_i][_qp];
  Real conduction_part = _k[_qp] * (_grad_phi[_j][_qp] * _grad_test[_i][_qp]);

  return convective_part + conduction_part;
}

Real
NSTemperature::computeQpOffDiagJacobian(unsigned jvar)
{
  if (jvar == _u_vel_var_number)
  {
    Real convective_part = _rho[_qp] * _cp[_qp] * _phi[_j][_qp] * _grad_u[_qp](0) * _test[_i][_qp];
    return convective_part;
  }

  else if (jvar == _v_vel_var_number)
  {
    Real convective_part = _rho[_qp] * _cp[_qp] * _phi[_j][_qp] * _grad_u[_qp](1) * _test[_i][_qp];
    return convective_part;
  }

  else if (jvar == _w_vel_var_number)
  {
    Real convective_part = _rho[_qp] * _cp[_qp] * _phi[_j][_qp] * _grad_u[_qp](2) * _test[_i][_qp];
    return convective_part;
  }

  else if (jvar == _p_var_number)
  {
    Real compress_part = _phi[_j][_qp] * (_grad_u_vel[_qp](0) + _grad_v_vel[_qp](1) + _grad_w_vel[_qp](2));
    return compress_part;
  }

  else if (jvar == _rho_var_number)
  {
    Real convective_part = _phi[_j][_qp] * _cp[_qp] *
                           (_u_vel[_qp] * _grad_u[_qp](0) + _v_vel[_qp] * _grad_u[_qp](1) +
                           _w_vel[_qp] * _grad_u[_qp](2)) * _test[_i][_qp];
    return convective_part;
  }

  else
    return 0;
}
