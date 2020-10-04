#include "Deformation_y.h"

registerMooseObject("ExampleApp", Deformation_y);

template <>
InputParameters
validParams<Deformation_y>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Deformation_y equation 2");
  params.addRequiredCoupledVar("u", "x-deformation");
  params.addParam<MaterialPropertyName>("E_name", "E", "Young's Modulus");
  params.addParam<MaterialPropertyName>("nu_name", "nu", "Poisson's ratio");
  return params;
}

Deformation_y::Deformation_y(const InputParameters & parameters)
  : Kernel(parameters),
    _u_def(coupledValue("u")),
    _grad_u_def(coupledGradient("u")),
    _E(getMaterialProperty<Real>("E_name")),
    _nu(getMaterialProperty<Real>("nu_name"))
{
}

Real
Deformation_y::computeQpResidual()
{
  Real c = _E[_qp];
  Real d = _E[_qp] * _nu[_qp];
  return - (d * _grad_u_def[_qp](0) + d * _grad_u[_qp](1)) * _grad_test[_i][_qp](1);
}