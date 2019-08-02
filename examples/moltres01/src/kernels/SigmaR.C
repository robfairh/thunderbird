#include "SigmaR.h"

registerMooseObject("ExampleApp", SigmaR);

template <>
InputParameters
validParams<SigmaR>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("remxs", 1.0, "Removal cross section");
  params.addRequiredParam<unsigned int>("group_number", "The current energy group.");
  return params;
}

SigmaR::SigmaR(const InputParameters & parameters)
  : Kernel(parameters),
    _remxs(getParam<Real>("remxs")),
    _group(getParam<unsigned int>("group_number") - 1)
{
}

Real
SigmaR::computeQpResidual()
{
  return _test[_i][_qp] * _remxs * _u[_qp];
}

Real
SigmaR::computeQpJacobian()
{
  return _test[_i][_qp] * _remxs * _phi[_j][_qp];
}
