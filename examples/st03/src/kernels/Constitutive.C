#include "Constitutive.h"

registerMooseObject("ExampleApp", Constitutive);

template <>
InputParameters
validParams<Constitutive>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Constitutive equation");
  params.addRequiredCoupledVar("sigma_x", "stress in x-direction");
  params.addParam<MaterialPropertyName>("E_name", "E", "Young's modulus");
  params.addParam<MaterialPropertyName>("nu_name", "nu", "Poisson ratio");
  return params;
}

Constitutive::Constitutive(const InputParameters & parameters)
  : Kernel(parameters),    
    _sigma_x(coupledValue("sigma_x")),
    _E(getMaterialProperty<Real>("E_name")),
    _nu(getMaterialProperty<Real>("nu_name"))
{
}

Real
Constitutive::computeQpResidual()
{
  Real res = 0;

  res += _E[_qp] * _u[_qp] * _test[_i][_qp];
  res += -_sigma_x[_qp] * _test[_i][_qp];

  return res;
}