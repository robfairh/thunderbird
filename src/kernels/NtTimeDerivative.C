#include "NtTimeDerivative.h"

registerMooseObject("thunderbirdApp", NtTimeDerivative);

template <>
InputParameters
validParams<NtTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addParam<Real>("time_derivative_coeff", 1.0, "Time Coefficient");
  return params;
}

NtTimeDerivative::NtTimeDerivative(const InputParameters & parameters)
  : TimeDerivative(parameters),
    _time_derivative_coeff(getParam<Real>("time_derivative_coeff"))
{
}

Real
NtTimeDerivative::computeQpResidual()
{
  return _time_derivative_coeff * TimeDerivative::computeQpResidual();
}

Real
NtTimeDerivative::computeQpJacobian()
{
  return _time_derivative_coeff * TimeDerivative::computeQpJacobian();
}
