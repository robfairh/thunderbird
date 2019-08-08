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
  
  const VariableValue & _p;
  const VariableGradient & _grad_p;
  unsigned _p_var_number;

  unsigned _component;
  const Real & _mu;
};

#endif
