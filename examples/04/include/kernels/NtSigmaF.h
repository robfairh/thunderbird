#ifndef NTSIGMAF_H
#define NTSIGMAF_H

#include "Kernel.h"

class NtSigmaF;

template <>
InputParameters validParams<NtSigmaF>();

class NtSigmaF : public Kernel
{
public:
  NtSigmaF(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _nu;
  Real _xsf;
};

#endif // NTSIGMAF_H
