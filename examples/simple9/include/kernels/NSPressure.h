#ifndef NSPRESSURE_H
#define NSPRESSURE_H

#include "Kernel.h"

// Forward Declarations
class NSPressure;

template <>
InputParameters validParams<NSPressure>();

class NSPressure : public Kernel
{
public:
  NSPressure(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  //const Real & _R;
  const VariableValue & _rho;
  const VariableValue & _temp;

};

#endif // NSPRESSURE_H
