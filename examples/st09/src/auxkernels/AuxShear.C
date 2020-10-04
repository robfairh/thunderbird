#include "AuxShear.h"

registerMooseObject("ExampleApp", AuxShear);

template <>
InputParameters
validParams<AuxShear>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("u_def", "deformation in x-direction");
  params.addRequiredCoupledVar("v_def", "deformation in y-direction");

  params.addParam<Real>("E", 1.0, "Young's Modulus");
  params.addParam<Real>("nu", 1.0, "Poisson ratio");
  return params;
}

AuxShear::AuxShear(const InputParameters & parameters)
  : AuxKernel(parameters),    
    _u_def(coupledValue("u_def")),
    _v_def(coupledValue("v_def")),
    _grad_u_def(coupledGradient("u_def")),
    _grad_v_def(coupledGradient("v_def")),

    _E(getParam<Real>("E")),
    _nu(getParam<Real>("nu"))
{
}

Real
AuxShear::computeValue()
{
  Real shear_strain = 0;
  Real G = _E/2/(1+_nu);
  
  shear_strain = _grad_u_def[_qp](1) + _grad_v_def[_qp](0);

  return G * shear_strain;
}