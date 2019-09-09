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

  const VariableValue & _variable;
  const Real & _constant;
};

#endif // NSMASSAUX_H
