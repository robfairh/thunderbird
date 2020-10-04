#include "NSMomentum.h"

registerMooseObject("ExampleApp", NSMomentum);

template <>
InputParameters
validParams<NSMomentum>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Simple NS.");
  //params.addRequiredCoupledVar("rho", "density");
  params.addRequiredCoupledVar("p", "pressure");
  params.addParam<MaterialPropertyName>("mu_name", "mu", "Dynamic viscosity");
  return params;
}

NSMomentum::NSMomentum(const InputParameters & parameters)
  : Kernel(parameters),
    //_rho(coupledValue("rho")),
    //_grad_rho(coupledGradient("rho")),
    _p(coupledValue("p")),
    _grad_p(coupledGradient("p")),
    _mu(getMaterialProperty<Real>("mu_name"))
{
}

Real
NSMomentum::computeQpResidual()
{
  Real r = 0;

  //r += _test[_i][_qp] * _rho[_qp] * _u[_qp] * _grad_u[_qp] (0);
  r += _test[_i][_qp] * _u[_qp] * _grad_u[_qp] (0);
  r += - _grad_p[_qp](0) * _test[_i][_qp];
  r += _mu[_qp] * (_grad_u[_qp] * _grad_test[_i][_qp]);

  return r;
}
