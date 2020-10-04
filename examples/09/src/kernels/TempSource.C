#include "TempSource.h"

registerMooseObject("ExampleApp", TempSource);

template <>
InputParameters
validParams<TempSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("src", 1.0, "Distributed Source");
  return params;
}

TempSource::TempSource(const InputParameters & parameters)
  : Kernel(parameters),
    _src(getParam<Real>("src"))
{
}

Real
TempSource::computeQpResidual()
{
  return _test[_i][_qp] * -_src;
}