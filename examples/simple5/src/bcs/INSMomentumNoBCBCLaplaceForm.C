//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "INSMomentumNoBCBCLaplaceForm.h"
#include "MooseMesh.h"

registerMooseObject("ExampleApp", INSMomentumNoBCBCLaplaceForm);

template <>
InputParameters
validParams<INSMomentumNoBCBCLaplaceForm>()
{
  InputParameters params = validParams<IntegratedBC>();

  params.addClassDescription("This class implements the 'No BC' boundary condition based on the "
                             "'Laplace' form of the viscous stress tensor.");
  params.addParam<MaterialPropertyName>("mu_name", "mu", "The name of the dynamic viscosity");
  return params;
}

INSMomentumNoBCBCLaplaceForm::INSMomentumNoBCBCLaplaceForm(const InputParameters & parameters)
  : IntegratedBC(parameters),
  _mu(getMaterialProperty<Real>("mu_name"))
{
}

Real
INSMomentumNoBCBCLaplaceForm::computeQpResidual()
{
  // -mu * (grad(u).n) * test
  Real viscous_part = -_mu[_qp] * (_grad_u[_qp] * _normals[_qp]) * _test[_i][_qp];

  return viscous_part;
}
