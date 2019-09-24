#include "Deformation.h"

registerMooseObject("ExampleApp", Deformation);

template <>
InputParameters
validParams<Deformation>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Deformation equation");
  params.addRequiredCoupledVar("strain_x", "Strain in x-direction");
  params.addRequiredCoupledVar("strain_y", "Strain in y-direction");
  params.addRequiredParam<unsigned>("component", "Deformation direction.");
  return params;
}

Deformation::Deformation(const InputParameters & parameters)
  : Kernel(parameters),
   _strain_x(coupledValue("strain_x")),
   _strain_y(coupledValue("strain_y")),
   _component(getParam<unsigned>("component"))
{
}

Real
Deformation::computeQpResidual()
{
  Real res = 0;

  res += _grad_u[_qp](_component) * _test[_i][_qp];

  RealVectorValue strain(_strain_x[_qp], _strain_y[_qp]);
  res += - strain(_component) * _test[_i][_qp];

  return res;
}