#include "Deformation_x.h"

registerMooseObject("ExampleApp", Deformation_x);

template <>
InputParameters
validParams<Deformation_x>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Deformation_x equation 1");
  params.addRequiredCoupledVar("v", "y-deformation");
  params.addParam<MaterialPropertyName>("E_name", "E", "Young's Modulus");
  params.addParam<MaterialPropertyName>("nu_name", "nu", "Poisson's ratio");
  return params;
}

Deformation_x::Deformation_x(const InputParameters & parameters)
  : Kernel(parameters),
    _v_def(coupledValue("v")),
    _grad_v_def(coupledGradient("v")),
    _E(getMaterialProperty<Real>("E_name")),
    _nu(getMaterialProperty<Real>("nu_name"))
{
}

Real
Deformation_x::computeQpResidual()
{
  Real c = _E[_qp];
  Real d = _E[_qp] * _nu[_qp];
  return - (c * _grad_u[_qp](0) + d * _grad_v_def[_qp](1)) * _grad_test[_i][_qp](0);
}