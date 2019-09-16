#ifndef NSTEMPERATURE_H
#define NSTEMPERATURE_H

#include "Kernel.h"

class NSTemperature;

template <>
InputParameters validParams<NSTemperature>();

class NSTemperature : public Kernel
{
public:
  NSTemperature(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  //virtual Real computeQpJacobian();
  //virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Coupled variables
  const VariableValue & _u_vel;
  const VariableValue & _p;
  const VariableValue & _rho;

  const VariableGradient & _grad_u_vel;

  // Required parameters
  const MaterialProperty<Real> & _k;
  const MaterialProperty<Real> & _cp;
};

#endif // NSTEMPERATURE_H
