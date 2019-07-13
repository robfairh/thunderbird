//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef CONVECTION_H
#define CONVECTION_H

#include "Kernel.h"

class Convection;

template <>
InputParameters validParams<Convection>();

class Convection : public Kernel
{
public:
  Convection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  RealVectorValue _velocity;
};

#endif // CONVECTION_H
