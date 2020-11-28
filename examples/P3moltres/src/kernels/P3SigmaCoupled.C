#include "P3SigmaCoupled.h"

registerMooseObject("ExampleApp", P3SigmaCoupled);

template <>
InputParameters
validParams<P3SigmaCoupled>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("val", 1.0, "Scattering Cross Section");


  params.addRequiredCoupledVar("second_flux", "Second flux");
  return params;
}

P3SigmaCoupled::P3SigmaCoupled(const InputParameters & parameters)
  : Kernel(parameters),
    _val(getParam<Real>("val")),
    _second_flux = &coupledValue("second_flux")
{
}

Real
P3SigmaCoupled::computeQpResidual()
{
  return _test[_i][_qp] * _val * _second_flux[_qp];
}

Real
P3SigmaCoupled::computeQpJacobian()
{
  return 0.;
}
