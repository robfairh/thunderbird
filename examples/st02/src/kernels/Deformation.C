#include "Deformation.h"

registerMooseObject("ExampleApp", Deformation);

template <>
InputParameters
validParams<Deformation>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Deformation equation");
  params.addRequiredCoupledVar("strain_x", "Strain in x-direction");
  return params;
}

Deformation::Deformation(const InputParameters & parameters)
  : Kernel(parameters),
   _strain_x(coupledValue("strain_x"))
{
}

Real
Deformation::computeQpResidual()
{
  Real res = 0;

  res += _grad_u[_qp](0) * _test[_i][_qp];
  res += - _strain_x[_qp] * _test[_i][_qp];

  return res;
}