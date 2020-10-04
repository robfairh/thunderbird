#include "Equilibrium.h"

registerMooseObject("ExampleApp", Equilibrium);

template <>
InputParameters
validParams<Equilibrium>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Equilibrium equation");
  params.addParam<MaterialPropertyName>("rho_name", "rho", "Density");
  return params;
}

Equilibrium::Equilibrium(const InputParameters & parameters)
  : Kernel(parameters),
    _rho(getMaterialProperty<Real>("rho_name"))
{
}

Real
Equilibrium::computeQpResidual()
{
  Real res = 0;

  res += _grad_u[_qp](0) * _test[_i][_qp];
  res += _rho[_qp] * 9.81 * _test[_i][_qp];

  return res;
}