#include "P3SigmaR.h"

registerMooseObject("ExampleApp", P3SigmaR);

template <>
InputParameters
validParams<P3SigmaR>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("remxs", 1.0, "Removal cross section");
  return params;
}

P3SigmaR::P3SigmaR(const InputParameters & parameters)
  : Kernel(parameters),
    _remxs(getParam<Real>("remxs"))
{
}

Real
P3SigmaR::computeQpResidual()
{
  return _test[_i][_qp] * _remxs * _u[_qp];
}

Real
P3SigmaR::computeQpJacobian()
{
  return _test[_i][_qp] * _remxs * _phi[_j][_qp];
}
