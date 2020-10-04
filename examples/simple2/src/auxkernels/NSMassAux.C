#include "NSMassAux.h"

registerMooseObject("ExampleApp", NSMassAux);

template <>
InputParameters
validParams<NSMassAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<Real>("constant", 1.0, "Scalar value subtracted from compareVar");
  params.addRequiredCoupledVar("compareVar", "Coupled variable");
  params.declareControllable("constant");
  return params;
}

NSMassAux::NSMassAux(const InputParameters & parameters)
  : AuxKernel(parameters),

    // We can couple in a value from one of our kernels with a call to coupledValueAux
    _variable(coupledValue("compareVar")),

    // Set our member scalar value from InputParameters (read from the input file)
    _constant(getParam<Real>("constant"))
{
}

Real
NSMassAux::computeValue()
{
  return (_constant/_variable[_qp]);
}
