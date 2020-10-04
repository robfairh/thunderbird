#ifndef NTSIGMAR_H
#define NTSIGMAR_H

#include "Kernel.h"

class NtSigmaR;

template <>
InputParameters validParams<NtSigmaR>();

class NtSigmaR : public Kernel
{
public:
  NtSigmaR(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const Real & _xsr;
};

#endif // NTSIGMAR_H
