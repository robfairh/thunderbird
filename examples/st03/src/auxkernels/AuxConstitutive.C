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
  //params.addParam<MaterialPropertyName>("E_name", "E", "Young");
  //params.addParam<MaterialPropertyName>("nu_name", "nu", "Poisson ratio");
  return params;
}

AuxConstitutive::AuxConstitutive(const InputParameters & parameters)
  : AuxKernel(parameters),    
    _sigma_x(coupledValue("sigma_x")),
    _sigma_y(coupledValue("sigma_y")),
    _component(getParam<unsigned>("component")),
    _E(getParam<Real>("E"))
    //_E(getMaterialProperty<Real>("E_name"))
    //_nu(getMaterialProperty<Real>("nu_name"))
{
}

Real
AuxConstitutive::computeValue()
{
  RealVectorValue sigma(_sigma_x[_qp], _sigma_y[_qp]);
  return sigma(_component)/_E;
}