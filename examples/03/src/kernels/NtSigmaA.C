#include "NtSigmaA.h"

registerMooseObject("ExampleApp", NtSigmaA);

template <>
InputParameters
validParams<NtSigmaA>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("xsa", 1.0, "Absortion Cross Section");
  return params;
}

NtSigmaA::NtSigmaA(const InputParameters & parameters)
  : Kernel(parameters),
    _xsa(getParam<Real>("xsa"))
{
}

Real
NtSigmaA::computeQpResidual()
{
  return _test[_i][_qp] * _xsa * _u[_qp];
}

Real
NtSigmaA::computeQpJacobian()
{
  return _test[_i][_qp] * _xsa * _phi[_j][_qp];
}