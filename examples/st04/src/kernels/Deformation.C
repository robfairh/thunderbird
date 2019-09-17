#include "Deformation.h"

registerMooseObject("ExampleApp", Deformation);

template <>
InputParameters
validParams<Deformation>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Deformation equation 1");
  params.addParam<MaterialPropertyName>("E_name", "E", "Young's Modulus");
  params.addParam<MaterialPropertyName>("nu_name", "nu", "Poisson's ratio");
  return params;
}

Deformation::Deformation(const InputParameters & parameters)
  : Kernel(parameters),
    _E(getMaterialProperty<Real>("E_name")),
    _nu(getMaterialProperty<Real>("nu_name"))
{
}

Real
Deformation::computeQpResidual()
{
  Real c = _E[_qp];
  return - c * _grad_u[_qp](0) * _grad_test[_i][_qp](0);
}