#include "Equilibrium2.h"

registerMooseObject("ExampleApp", Equilibrium2);

template <>
InputParameters
validParams<Equilibrium2>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("Equilibrium equation");
  params.addRequiredParam<unsigned>("component", "Stress direction.");
  params.addParam<MaterialPropertyName>("rho_name", "rho", "Density");
  params.addParam<RealVectorValue>("gravity", RealVectorValue(0, 0, 0), "Direction of the gravity vector");
  return params;
}

Equilibrium2::Equilibrium2(const InputParameters & parameters)
  : Kernel(parameters),
    _component(getParam<unsigned>("component")),
    _rho(getMaterialProperty<Real>("rho_name")),
    _gravity(getParam<RealVectorValue>("gravity"))
{
}

Real
Equilibrium2::computeQpResidual()
{
  Real res = 0;
  
  res += +_rho[_qp] * _gravity(_component) * _test[_i][_qp];

  return res;
}