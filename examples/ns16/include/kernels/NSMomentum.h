#ifndef NSMOMENTUM_H
#define NSMOMENTUM_H

#include "Kernel.h"

class NSMomentum;

template <>
InputParameters validParams<Kernel>();

/**
 * This class computes momentum equation residual and Jacobian viscous
 * contributions for the "Laplacian" form of the governing equations.
 */
class NSMomentum : public Kernel
{
public:
  NSMomentum(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned jvar) override;
  
  virtual RealVectorValue dConvecDUComp(unsigned comp);

  const VariableValue & _u_vel;
  const VariableValue & _v_vel;
  const VariableValue & _w_vel;
  const VariableValue & _rho;
  const VariableValue & _temp;

  const VariableGradient & _grad_u_vel;
  const VariableGradient & _grad_v_vel;
  const VariableGradient & _grad_w_vel;
  const VariableGradient & _grad_rho;
  const VariableGradient & _grad_temp;

  unsigned _u_vel_var_number;
  unsigned _v_vel_var_number;
  unsigned _w_vel_var_number;
  unsigned _rho_var_number;
  unsigned _temp_var_number;

  unsigned _component;
  
  // Material properties
  const MaterialProperty<Real> & _mu;
  const MaterialProperty<Real> & _R;

  RealVectorValue _gravity;
};

#endif
