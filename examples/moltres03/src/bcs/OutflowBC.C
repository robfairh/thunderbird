#include "OutflowBC.h"
#include "Function.h"

registerMooseObject("ExampleApp", OutflowBC);

template <>
InputParameters
validParams<OutflowBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredParam<RealVectorValue>("velocity", "Velocity vector");
  params.addClassDescription("DG upwinding for the convection");
  return params;
}

OutflowBC::OutflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _velocity(getParam<RealVectorValue>("velocity"))
{
}

Real
OutflowBC::computeQpResidual()
{
  Real r = 0;

  Real vdotn = _velocity * _normals[_qp];

  if (vdotn >= 0)
    r += vdotn * _u[_qp] * _test[_i][_qp];

  return r;

  //This one is the one in moose, it doesn't care about the sign of normals
  //return _test[_i][_qp] * _u[_qp] * _velocity * _normals[_qp];
}

Real
OutflowBC::computeQpJacobian()
{
  Real r = 0;

  Real vdotn = _velocity * _normals[_qp];

  if (vdotn >= 0)
    r += vdotn * _phi[_j][_qp] * _test[_i][_qp];

  return r;

  //Same as the one in QpResidual
  //return _test[_i][_qp] * _phi[_j][_qp] * _velocity * _normals[_qp];
}
