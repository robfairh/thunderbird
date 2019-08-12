#ifndef NSTIMEMOMENTUM_H
#define NSTIMEMOMENTUM_H

#include "TimeDerivative.h"

// Forward Declarations
class NSTimeMomentum;

template <>
InputParameters validParams<NSTimeMomentum>();

class NSTimeMomentum : public TimeDerivative
{
public:
  NSTimeMomentum(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Parameters
  const VariableValue & _rho;
  unsigned _rho_var_number;

};

#endif // NSTIMEMOMENTUM_H
