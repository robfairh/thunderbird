#include "Shear_y.h"

registerMooseObject("ExampleApp", Shear_y);

template <>
InputParameters
validParams<Shear_y>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Shear_y equation 2");
  params.addRequiredCoupledVar("u", "x-deformation");
  params.addParam<MaterialPropertyName>("E_name", "E", "Young's Modulus");
  params.addParam<MaterialPropertyName>("nu_name", "nu", "Poisson's ratio");
  return params;
}

Shear_y::Shear_y(const InputParameters & parameters)
  : Kernel(parameters),
    _u_def(coupledValue("u")),
    _grad_u_def(coupledGradient("u")),
    _E(getMaterialProperty<Real>("E_name")),
    _nu(getMaterialProperty<Real>("nu_name"))
{
}

Real
Shear_y::computeQpResidual()
{
  Real G = _E[_qp]/2;
  return - G * (_grad_u[_qp](1) + _grad_v_def[_qp](0)) * _grad_test[_i][_qp](0);
}