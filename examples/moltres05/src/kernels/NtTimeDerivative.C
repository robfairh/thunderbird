#include "NtTimeDerivative.h"

registerMooseObject("ExampleApp", NtTimeDerivative);

template <>
InputParameters
validParams<NtTimeDerivative>()
{
  InputParameters params = validParams<TimeDerivative>();
  params.addRequiredParam<unsigned int>("group_number",
                                        "The group for which this kernel controls diffusion");
  params.addCoupledVar("temperature",
                       "The temperature used to interpolate the diffusion coefficient");
  return params;
}

NtTimeDerivative::NtTimeDerivative(const InputParameters & parameters)
  : TimeDerivative(parameters),
    _recipvel(getMaterialProperty<std::vector<Real>>("recipvel")),
    _d_recipvel_d_temp(getMaterialProperty<std::vector<Real>>("d_recipvel_d_temp")),
    _group(getParam<unsigned int>("group_number") - 1),
    _temp_id(coupled("temperature"))
{
}

Real
NtTimeDerivative::computeQpResidual()
{
  return _recipvel[_qp][_group] * TimeDerivative::computeQpResidual();
}

Real
NtTimeDerivative::computeQpJacobian()
{
  return _recipvel[_qp][_group] * TimeDerivative::computeQpJacobian();
}
