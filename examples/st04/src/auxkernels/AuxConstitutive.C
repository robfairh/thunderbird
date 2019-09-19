#include "AuxConstitutive.h"

registerMooseObject("ExampleApp", AuxConstitutive);

template <>
InputParameters
validParams<AuxConstitutive>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("u_def", "deformation in x-direction");
  params.addParam<MaterialPropertyName>("E_name", "E", "Young Modulus");
  //params.addParam<Real>("E", 1.0, "Young's Modulus");
  return params;
}

AuxConstitutive::AuxConstitutive(const InputParameters & parameters)
  : AuxKernel(parameters),    
    _u_def(coupledValue("u_def")),
    _grad_u_def(coupledGradient("u_def")),
    //_E(getParam<Real>("E"))
    _E(getMaterialProperty<Real>("E_name"))
    //_nu(getMaterialProperty<Real>("nu_name"))
{
}

Real
AuxConstitutive::computeValue()
{
  return _E[_qp] * _grad_u_def[_qp](0);
  //return _grad_u_def[_qp](0);
}