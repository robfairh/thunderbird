#include "SigmaR.h"

registerMooseObject("ExampleApp", SigmaR);

template <>
InputParameters
validParams<SigmaR>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<unsigned int>("group_number", "The current energy group.");
  params.addCoupledVar("temperature", "The temperature used to interpolate material properties");
  return params;
}

SigmaR::SigmaR(const InputParameters & parameters)
  : Kernel(parameters),
    _remxs(getMaterialProperty<std::vector<Real>>("remxs")),
    _d_remxs_d_temp(getMaterialProperty<std::vector<Real>>("d_remxs_d_temp")),
    _group(getParam<unsigned int>("group_number") - 1),
    _temp_id(coupled("temperature"))
{
}

Real
SigmaR::computeQpResidual()
{
  //return _test[_i][_qp] * _remxs[_qp][_group] * computeConcentration(_u, _qp);
  return _test[_i][_qp] * _remxs[_qp][_group] * _u[_qp];
}

Real
SigmaR::computeQpJacobian()
{
  //return _test[_i][_qp] * _remxs[_qp][_group] * computeConcentrationDerivative(_u, _phi, _j, _qp);
  return _test[_i][_qp] * _remxs[_qp][_group] * _phi[_j][_qp];
}
