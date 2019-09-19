#ifndef NSTIMETEMPERATURE_H
#define NSTIMETEMPERATURE_H

#include "TimeDerivative.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class NSTimeTemperature;

template <>
InputParameters validParams<NSTimeTemperature>();

class NSTimeTemperature
    : public DerivativeMaterialInterface<JvarMapKernelInterface<TimeDerivative>>
{
public:
  NSTimeTemperature(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  //virtual Real computeQpJacobian() override;
  //virtual Real computeQpOffDiagJacobian(unsigned jvar) override;

  const VariableValue & _rho;
  unsigned _rho_var_number;

  const MaterialProperty<Real> & _cv;
};

#endif // NSTIMETEMPERATURE_H
