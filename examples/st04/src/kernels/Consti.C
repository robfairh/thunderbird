#include "Consti.h"

registerMooseObject("ExampleApp", Consti);

template <>
InputParameters
validParams<Consti>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Consti equation 1");
  params.addRequiredCoupledVar("u_def", "deformation in x-direction");
  params.addParam<MaterialPropertyName>("E_name", "E", "Young's Modulus");
  return params;
}

Consti::Consti(const InputParameters & parameters)
  : Kernel(parameters),
    _u_def(coupledValue("u_def")),
    _grad_u_def(coupledGradient("u_def")),
    _E(getMaterialProperty<Real>("E_name"))
{
}

Real
Consti::computeQpResidual()
{
  return (_u[_qp] - _E[_qp] * _grad_u_def[_qp](0)) * _test[_i][_qp];
}