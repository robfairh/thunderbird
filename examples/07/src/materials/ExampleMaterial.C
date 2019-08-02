#include "ExampleMaterial.h"

registerMooseObject("ExampleApp", ExampleMaterial);

template <>
InputParameters
validParams<ExampleMaterial>()
{
  InputParameters params = validParams<Material>();
  params.addRequiredParam<std::vector<Real>>(
      "independent_vals",
      "The vector of z-coordinate values for a piecewise function's independent variable");
  params.addRequiredParam<std::vector<Real>>(
      "dependent_vals", "The vector of diffusivity values for a piecewise function's dependent");
  params.addCoupledVar(
      "temperature", 5, "The temperature.");

  return params;
}

ExampleMaterial::ExampleMaterial(const InputParameters & parameters)
  : Material(parameters),
    _temperature(coupledValue("temperature")),
    _diffusivity(declareProperty<Real>("diffusivity")),
    _piecewise_func(getParam<std::vector<Real>>("independent_vals"),
                    getParam<std::vector<Real>>("dependent_vals"))
{
}

void
ExampleMaterial::computeQpProperties()
{
  _diffusivity[_qp] = _piecewise_func.sample(_temperature[_qp]);
  //_diffusivity[_qp] = _piecewise_func.sample(_q_point[_qp](2));
}
