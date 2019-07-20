#ifndef NTSIGMAA_H
#define NTSIGMAA_H

#include "Kernel.h"

class NtSigmaA;

template <>
InputParameters validParams<NtSigmaA>();

class NtSigmaA : public Kernel
{
public:
  NtSigmaA(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const Real & _xsa; //Why not jsut Real _xsa; ??
};

#endif // NTSIGMAA_H
