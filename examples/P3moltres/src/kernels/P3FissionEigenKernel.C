#include "P3FissionEigenKernel.h"

registerMooseObject("ExampleApp", P3FissionEigenKernel);

template <>
InputParameters
validParams<P3FissionEigenKernel>()
{
  InputParameters params = validParams<EigenKernel>();
  params.addRequiredCoupledVar("second_flux", "Second flux");
  params.addParam<Real>("chit", 1.0, "chi total");
  params.addParam<Real>("nsf", 1.0, "nu sigma f");
  params.addParam<Real>("val1", 1.0, "first constant");
  params.addParam<Real>("val2", 1.0, "second constant");
  return params;
}

P3FissionEigenKernel::P3FissionEigenKernel(const InputParameters & parameters)
  : EigenKernel(parameters),
    _second_flux(coupledValue("second_flux")),
    _chi_t(getParam<Real>("chit")),
    _nsf(getParam<Real>("nsf")),
    _val1(getParam<Real>("val1")),
    _val2(getParam<Real>("val2"))
{
}

Real
P3FissionEigenKernel::computeQpResidual()
{
  return -_test[_i][_qp] * _chi_t * _nsf * (_val1 * _u[_qp] + _val2 * _second_flux[_qp]);
}

Real
P3FissionEigenKernel::computeQpJacobian()
{
  return -_test[_i][_qp] * _chi_t * _nsf * _val1 * _phi[_j][_qp];
}
