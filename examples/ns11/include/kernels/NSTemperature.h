//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#ifndef NSTEMPERATURE_H
#define NSTEMPERATURE_H

#include "Kernel.h"

class NSTemperature;

template <>
InputParameters validParams<NSTemperature>();

/**
 * This class computes the residual and Jacobian contributions for the
 * incompressible Navier-Stokes temperature (energy) equation.
 */
class NSTemperature : public Kernel
{
public:
  NSTemperature(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Coupled variables
  const VariableValue & _u_vel;
  const VariableValue & _v_vel;
  const VariableValue & _w_vel;
  const VariableValue & _rho;

  // Variable numberings
  unsigned _u_vel_var_number;
  unsigned _v_vel_var_number;
  unsigned _w_vel_var_number;
  unsigned _rho_var_number;

  // Required parameters
  const MaterialProperty<Real> & _k;
  const MaterialProperty<Real> & _cp;
};

#endif // INSTEMPERATURE_H
