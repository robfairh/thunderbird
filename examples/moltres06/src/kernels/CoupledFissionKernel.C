#include "CoupledFissionKernel.h"

registerMooseObject("ExampleApp", CoupledFissionKernel);

template <>
InputParameters
validParams<CoupledFissionKernel>()
{
  InputParameters params = validParams<Kernel>();
  params.addParam<Real>("nfxs", 1.0, "Nu Sigma F XS");
  return params;
}

CoupledFissionKernel::CoupledFissionKernel(const InputParameters & parameters)
  : Kernel(parameters),
    _nfxs(getParam<Real>("nfxs"))
{
}

Real
CoupledFissionKernel::computeQpResidual()
{
  Real r = 0; 
  r += -_test[_i][_qp] * _nfxs * _u[_qp];
  return r;
}

Real
CoupledFissionKernel::computeQpJacobian()
{
  Real jac = 0;
  jac = _test[_i][_qp] -_nfxs * _phi[_j][_qp];
  return jac;
}