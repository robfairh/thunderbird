#include "NSMomentum.h"

registerMooseObject("ExampleApp", NSMomentum);

template <>
InputParameters
validParams<NSMomentum>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Simple NS.");

  params.addParam<MaterialPropertyName>("mu_name", "mu", "Dynamic viscosity");
  params.addParam<MaterialPropertyName>("K_name", "K", "mass flow");
  return params;
}

NSMomentum::NSMomentum(const InputParameters & parameters)
  : Kernel(parameters),
    _mu(getMaterialProperty<Real>("mu_name")),
    _K(getMaterialProperty<Real>("K_name"))
{
}

Real
NSMomentum::computeQpResidual()
{
  Real r = 0;

  r += _test[_i][_qp] * _K[_qp] * _grad_u[_qp] (0);

  r += -10. *_test[_i][_qp];

  r += _mu[_qp] * (_grad_u[_qp] * _grad_test[_i][_qp]);

  return r;
}
