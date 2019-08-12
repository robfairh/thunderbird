#include "NSTimeDensity.h"

registerMooseObject("ExampleApp", NSTimeDensity);

template <>
InputParameters
validParams<NSTimeDensity>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addClassDescription("This class computes the time derivative for the "
                             "mass equation.");
  return params;
}

NSTimeDensity::NSTimeDensity(const InputParameters & parameters)
  : TimeDerivative(parameters)
{
}

Real
NSTimeDensity::computeQpResidual()
{
  return TimeDerivative::computeQpResidual();
}

Real
NSTimeDensity::computeQpJacobian()
{
  return TimeDerivative::computeQpJacobian();
}

Real
NSTimeDensity::computeQpOffDiagJacobian(unsigned)
{
  return 0.;
}
