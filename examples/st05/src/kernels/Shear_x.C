#include "Shear_x.h"

registerMooseObject("ExampleApp", Shear_x);

template <>
InputParameters
validParams<Shear_x>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Shear_x equation 1");
  params.addRequiredCoupledVar("v", "y-deformation");
  params.addParam<MaterialPropertyName>("E_name", "E", "Young's Modulus");
  params.addParam<MaterialPropertyName>("nu_name", "nu", "Poisson's ratio");
  return params;
}

Shear_x::Shear_x(const InputParameters & parameters)
  : Kernel(parameters),
    _v_def(coupledValue("v")),
    _grad_v_def(coupledGradient("v")),
    _E(getMaterialProperty<Real>("E_name")),
    _nu(getMaterialProperty<Real>("nu_name"))
{
}

Real
Shear_x::computeQpResidual()
{
  Real G = _E[_qp]/2;
  return - G * (_grad_u[_qp](1) + _grad_v_def[_qp](0)) * _grad_test[_i][_qp](1);
}