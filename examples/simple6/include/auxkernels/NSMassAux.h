#ifndef NSMASSAUX_H
#define NSMASSAUX_H

#include "AuxKernel.h"

// Forward Declarations
class NSMassAux;

template <>
InputParameters validParams<NSMassAux>();

class NSMassAux : public AuxKernel
{
public:
  NSMassAux(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  const VariableValue & _p;
  const VariableValue & _temp;

  const Real & _p_ref;
  const Real & _temp_ref;

  const Real & _bulk_m;
  const Real & _beta;

  const Real & _rho_ref;
};

#endif // NSMASSAUX_H
