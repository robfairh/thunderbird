#include "NSDensity.h"

registerMooseObject("ExampleApp", NSDensity);

template <>
InputParameters
validParams<NSDensity>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("This class computes the density equation residual and Jacobian "
                             "contributions for the Navier-Stokes momentum equation.");

  params.addRequiredCoupledVar("p", "pressure");
//  params.addRequiredCoupledVar("temp", "temperature variable");

  params.addParam<Real>("p_ref", 1.0, "reference pressure");
  params.addParam<Real>("temp_ref", 1.0, "reference temperature");

  params.addParam<Real>("bulk_m", 1.0, "bulk modulus");
  params.addParam<Real>("beta", 1.0, "thermal expansion coefficient");

  return params;
}

NSDensity::NSDensity(const InputParameters & parameters)
  : Kernel(parameters),

    _p(coupledValue("p")),
//    _temp(coupledValue("temp")),

    _p_var_number(coupled("p")),
//    _temp_var_number(coupled("temp")),

    _p_ref(getParam<Real>("p_ref")),
    _temp_ref(getParam<Real>("temp_ref")),

    _bulk_m(getParam<Real>("bulk_m")),
    _beta(getParam<Real>("beta")),
    _rho_ref(getMaterialProperty<Real>("rho_ref"))
{
}

Real
NSDensity::computeQpResidual()
{
  Real res = 0;

  res += (_u[_qp] - _rho_ref[_qp]) * _test[_i][_qp];
  //res += _rho_ref[_qp] * _beta * (_temp[_qp]-_temp_ref) * _test[_i][_qp];
  res += -_rho_ref[_qp]/_bulk_m * (_p[_qp]-_p_ref) * _test[_i][_qp];

  return res;
}

/*
Real
NSDensity::computeQpJacobian()
{
  //I think this is correct
  Real jac = 0;

  jac += _phi[_j][_qp] * _test[_i][_qp];

  return jac;
}

Real
NSDensity::computeQpOffDiagJacobian(unsigned jvar)
{
  //I think this is correct
  Real jac = 0;

  if (jvar == _p_var_number){
    jac += -_rho_ref[_qp]/_bulk_m * _phi[_j][_qp] * _test[_i][_qp];
  }
  
  if (jvar == _temp_var_number){
    jac += _rho_ref[_qp] * _beta * _phi[_j][_qp] * _test[_i][_qp];
  }

  return jac;
}
*/