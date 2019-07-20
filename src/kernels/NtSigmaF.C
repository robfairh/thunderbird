#include "NtSigmaF.h"

registerMooseObject("thunderbirdApp", NtSigmaF);

template <>
InputParameters
validParams<NtSigmaF>()
{
  InputParameters params = validParams<NtSigmaA>();
  params.addParam<Real>("nu", 1.0, "nu");
  params.addParam<Real>("xsf", 1.0, "Fission Cross Section");
  return params;
}

NtSigmaF::NtSigmaF(const InputParameters & parameters)
  : NtSigmaA(parameters),
    _nu(getParam<Real>("nu")),
    _xsf(getParam<Real>("xsf"))
{
}

Real
NtSigmaF::computeQpResidual()
{
  return _test[_i][_qp] * (-_nu * _xsf * _u[_qp]);
}

Real
NtSigmaF::computeQpJacobian()
{
  return _test[_i][_qp] * (-_nu * _xsf * _phi[_j][_qp]);
}