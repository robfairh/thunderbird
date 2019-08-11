#ifndef NSMOMENTUMTIMEDERIVATIVE_H
#define NSMOMENTUMTIMEDERIVATIVE_H

#include "TimeDerivative.h"

// Forward Declarations
class NSMomentumTimeDerivative;

template <>
InputParameters validParams<NSMomentumTimeDerivative>();

class NSMomentumTimeDerivative : public TimeDerivative
{
public:
  NSMomentumTimeDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Parameters
  const VariableValue & _rho;
  unsigned _rho_var_number;
};

#endif // NSMOMENTUMTIMEDERIVATIVE_H
