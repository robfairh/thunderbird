#include "NtSource.h"

registerMooseObject("ExampleApp", NtSource);

template <>
InputParameters
validParams<NtSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("src", 1.0, "Distributed Source");
  return params;
}

NtSource::NtSource(const InputParameters & parameters)
  : Kernel(parameters),
    _src(getParam<Real>("src"))
{
}

Real
NtSource::computeQpResidual()
{
  return _test[_i][_qp] * -_src;
}