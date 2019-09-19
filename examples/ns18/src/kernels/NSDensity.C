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
  params.addRequiredCoupledVar("temp", "temperature variable");

  params.addParam<Real>("R", 1.0, "Gases constant");
  
  return params;
}

NSDensity::NSDensity(const InputParameters & parameters)
  : Kernel(parameters),

    _p(coupledValue("p")),
    _temp(coupledValue("temp")),

    _R(getParam<Real>("R"))
{
}

Real
NSDensity::computeQpResidual()
{
  Real res = 0;

  res += _p[_qp] * _test[_i][_qp];
  res += -_u[_qp] * _R * _temp[_qp] * _test[_i][_qp];

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