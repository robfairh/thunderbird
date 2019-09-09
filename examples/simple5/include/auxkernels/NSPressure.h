#ifndef NSPRESSURE_H
#define NSPRESSURE_H

#include "AuxKernel.h"

// Forward Declarations
class NSPressure;

template <>
InputParameters validParams<NSPressure>();

class NSPressure : public AuxKernel
{
public:
  NSPressure(const InputParameters & parameters);

protected:
  virtual Real computeValue() override;

  //const Real & _R;
  const VariableValue & _rho;
  const VariableValue & _temp;

};

#endif // NSPRESSURE_H
