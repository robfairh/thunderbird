#ifndef CONSERVATIVETEMPERATUREADVECTION_H
#define CONSERVATIVETEMPERATUREADVECTION_H

#include "ConservativeAdvection.h"
#include "JvarMapInterface.h"
#include "DerivativeMaterialInterface.h"

// Forward Declaration
class ConservativeTemperatureAdvection;

template <>
InputParameters validParams<ConservativeTemperatureAdvection>();

class ConservativeTemperatureAdvection
    : public DerivativeMaterialInterface<JvarMapKernelInterface<ConservativeAdvection>>
{
public:
  ConservativeTemperatureAdvection(const InputParameters & parameters);

protected:
  virtual void initialSetup() override;
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const Real & _rho;
  const Real & _cp;
};

#endif // CONSERVATIVETEMPERATUREADVECTION_H
