#include "NSTimeMass.h"

registerMooseObject("ExampleApp", NSTimeMass);

template <>
InputParameters
validParams<NSTimeMass>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addClassDescription("This class computes the time derivative for the "
                             "mass equation.");
  return params;
}

NSTimeMass::NSTimeMass(const InputParameters & parameters)
  : TimeDerivative(parameters)
{
}

Real
NSTimeMass::computeQpResidual()
{
  return TimeDerivative::computeQpResidual();
}

/*
Real
NSTimeMass::computeQpJacobian()
{
  return TimeDerivative::computeQpJacobian();
}

Real
NSTimeMass::computeQpOffDiagJacobian(unsigned)
{
  return 0.;
}
*/