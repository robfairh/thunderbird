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
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned jvar) override;

  const VariableValue & _rho;
  unsigned _rho_var_number;

  const MaterialProperty<Real> & _cp;
  const MaterialProperty<Real> & _d_cp_d_u;
};

#endif // NSTIMETEMPERATURE_H
