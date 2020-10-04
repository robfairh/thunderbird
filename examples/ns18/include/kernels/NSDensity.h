#ifndef NSDENSITY_H
#define NSDENSITY_H

#include "Kernel.h"

class NSDensity;

template <>
InputParameters validParams<NSDensity>();

class NSDensity : public Kernel
{
public:
  NSDensity(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
//  virtual Real computeQpJacobian();
//  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  const VariableValue & _p;
  const VariableValue & _temp;

  unsigned _p_var_number;
  unsigned _temp_var_number;
  
  const Real & _R;
};

#endif // NSDENSITY_H