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

  const VariableValue & _rho;
  const VariableValue & _temp;

  unsigned _rho_var_number;
  unsigned _temp_var_number;
  
  const Real & _p_ref;
  const Real & _temp_ref;

  const Real & _bulk_m;
  const Real & _beta;

  const MaterialProperty<Real> & _rho_ref;
};

#endif // NSDENSITY_H