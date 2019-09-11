#include "NSTemperature.h"

registerMooseObject("ExampleApp", NSTemperature);

template <>
InputParameters
validParams<NSTemperature>()
{
  InputParameters params = validParams<Kernel>();

  params.addClassDescription("This class computes the residual and Jacobian contributions for the "
                             "Navier-Stokes temperature (energy) equation.");
  // Coupled variables
  params.addRequiredCoupledVar("u", "x-velocity");
  //params.addRequiredCoupledVar("p", "pressure");
  //params.addRequiredCoupledVar("rho", "density");

  // Optional parameters
  params.addParam<MaterialPropertyName>("k_name", "k", "thermal conductivity name");
  params.addParam<MaterialPropertyName>("cp_name", "cp", "specific heat name");
  
  return params;
}

NSTemperature::NSTemperature(const InputParameters & parameters)
  : Kernel(parameters),

    // Coupled variables
    _u_vel(coupledValue("u")),
    //_p(coupledValue("p")),
    //_rho(coupledValue("rho")),

    _grad_u_vel(coupledGradient("u")),

    // Material Properties
    _k(getMaterialProperty<Real>("k_name")),
    _cp(getMaterialProperty<Real>("cp_name"))
{
}

Real
NSTemperature::computeQpResidual()
{
  // Note: _u is the temperature variable, _grad_u is its gradient.
  Real convective_part = _rho[_qp] * _cp[_qp] * (_u_vel[_qp] * _grad_u[_qp](0)) * _test[_i][_qp];
  //Real convective_part = _cp[_qp] * (_u_vel[_qp] * _grad_u[_qp](0)) * _test[_i][_qp];

  // Thermal conduction part, k * grad(T) * grad(v)
  Real conduction_part = _k[_qp] * _grad_u[_qp] * _grad_test[_i][_qp];

  // Compressible flow
  //Real compress_part = _p[_qp] * (_grad_u_vel[_qp](0));

  //return convective_part + conduction_part + compress_part;
  return convective_part + conduction_part;
}