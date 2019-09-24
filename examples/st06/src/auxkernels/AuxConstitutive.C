#include "AuxConstitutive.h"

registerMooseObject("ExampleApp", AuxConstitutive);

template <>
InputParameters
validParams<AuxConstitutive>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("sigma_x", "stress in x-direction");
  params.addRequiredCoupledVar("sigma_y", "stress in y-direction");
  params.addRequiredParam<unsigned>("component", "Stress direction.");
  params.addParam<Real>("E", 1.0, "Young's Modulus");
  params.addParam<Real>("nu", 1.0, "Poisson ratio");
  return params;
}

AuxConstitutive::AuxConstitutive(const InputParameters & parameters)
  : AuxKernel(parameters),    
    _sigma_x(coupledValue("sigma_x")),
    _sigma_y(coupledValue("sigma_y")),
    _component(getParam<unsigned>("component")),
    _E(getParam<Real>("E")),
    _nu(getParam<Real>("nu"))
{
}

Real
AuxConstitutive::computeValue()
{
  Real strain = 0;
  RealVectorValue sigma(_sigma_x[_qp], _sigma_y[_qp]);

  if (_component == 0)
  {
    strain = 1/_E * (sigma(0) - _nu * sigma(1));
  }

  else if (_component == 1)
  {
    strain = 1/_E * (sigma(1) - _nu * sigma(0));
  }

  return strain;
}