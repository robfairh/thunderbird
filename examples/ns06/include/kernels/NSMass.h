#ifndef NSMASS_H
#define NSMASS_H

#include "Kernel.h"

class NSMass;

template <>
InputParameters validParams<NSMass>();

class NSMass : public Kernel
{
public:
  NSMass(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  const VariableValue & _u_vel;
  const VariableValue & _v_vel;

  const VariableGradient & _grad_u_vel;
  const VariableGradient & _grad_v_vel;

  unsigned _u_vel_var_number;
  unsigned _v_vel_var_number;

};

#endif // NSMASS_H
