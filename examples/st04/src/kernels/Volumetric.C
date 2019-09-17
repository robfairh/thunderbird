#include "Volumetric.h"

registerMooseObject("ExampleApp", Volumetric);

template <>
InputParameters
validParams<Volumetric>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Deformation equation 2");
  params.addParam<Real>("value", 0.0, "Volumetric force.");
  return params;
}

Volumetric::Volumetric(const InputParameters & parameters)
  : Kernel(parameters),
   _value(getParam<Real>("value"))
{
}

Real
Volumetric::computeQpResidual()
{
  return _value * _test[_i][_qp];
}