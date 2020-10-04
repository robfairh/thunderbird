#include "NSMomentum.h"

registerMooseObject("ExampleApp", NSMomentum);

template <>
InputParameters
validParams<NSMomentum>()
{
  InputParameters params = validParams<Kernel>();
  params.addClassDescription("This class computes momentum equation residual and Jacobian viscous "
                             "contributions for the 'Laplacian' form of the governing equations.");
  params.addRequiredCoupledVar("p", "pressure");
  params.addRequiredParam<unsigned>("component", "The velocity component that this is applied to.");
  params.addParam<Real>("mu", 1.0, "viscocity");
  return params;
}

NSMomentum::NSMomentum(const InputParameters & parameters)
  : Kernel(parameters),
    _p(coupledValue("p")),
    _grad_p(coupledGradient("p")),
    _p_var_number(coupled("p")),
    _component(getParam<unsigned>("component")),
    _mu(getParam<Real>("mu"))
{
}

Real
NSMomentum::computeQpResidual()
{
  Real r = _mu * (_grad_u[_qp] * _grad_test[_i][_qp]);
  r += _test[_i][_qp] * _grad_p[_qp](_component);

  return r;
}

Real
NSMomentum::computeQpJacobian()
{
  // Viscous part, Laplacian version
  return _mu * (_grad_phi[_j][_qp] * _grad_test[_i][_qp]);
}

Real
NSMomentum::computeQpOffDiagJacobian(unsigned jvar)
{
  Real jac = 0;
 
  if (jvar == _p_var_number)
  {
    jac += _test[_i][_qp] * _grad_phi[_j][_qp](_component);

    return jac;
  }

  else
    return 0;
}