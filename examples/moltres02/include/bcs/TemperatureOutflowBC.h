#ifndef TEMPERATUREOUTFLOWBC_H
#define TEMPERATUREOUTFLOWBC_H

#include "OutflowBC.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

class TemperatureOutflowBC;

template <>
InputParameters validParams<TemperatureOutflowBC>();

class TemperatureOutflowBC
    : public DerivativeMaterialInterface<JvarMapIntegratedBCInterface<OutflowBC>>
{
public:
  TemperatureOutflowBC(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const Real & _rho;
  const Real & _cp;
};

#endif // TEMPERATUREOUTFLOWBC_H
