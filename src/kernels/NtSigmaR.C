#include "NtSigmaR.h"

registerMooseObject("thunderbirdApp", NtSigmaR);

template <>
InputParameters
validParams<NtSigmaR>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("xsr", 1.0, "Removal Cross Section");
  return params;
}

NtSigmaR::NtSigmaR(const InputParameters & parameters)
  : Kernel(parameters),
    _xsr(getParam<Real>("xsr"))
{
}

Real
NtSigmaR::computeQpResidual()
{
  return _test[_i][_qp] * _xsr * _u[_qp];
}

Real
NtSigmaR::computeQpJacobian()
{
  return _test[_i][_qp] * _xsr * _phi[_j][_qp];
}