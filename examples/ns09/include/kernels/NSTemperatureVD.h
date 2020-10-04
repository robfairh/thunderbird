// Viscous Dissipation Function Kernel

#ifndef NSTEMPERATUREVD_H
#define NSTEMPERATUREVD_H

#include "Kernel.h"

class NSTemperatureVD;

template <>
InputParameters validParams<NSTemperatureVD>();

class NSTemperatureVD : public Kernel
{
public:
  NSTemperatureVD(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Coupled variables
  const VariableValue & _u_vel;
  const VariableValue & _v_vel;
  const VariableValue & _w_vel;

  const VariableGradient & _grad_u_vel;
  const VariableGradient & _grad_v_vel;
  const VariableGradient & _grad_w_vel;

  // Variable numberings
  unsigned _u_vel_var_number;
  unsigned _v_vel_var_number;
  unsigned _w_vel_var_number;

  // Required parameters
  const MaterialProperty<Real> & _rho;
  const MaterialProperty<Real> & _k;
  const MaterialProperty<Real> & _cp;
  const MaterialProperty<Real> & _mu;
};

#endif // INSTEMPERATUREVD_H
