#ifndef NTSOURCE_H
#define NTSOURCE_H

#include "Kernel.h"

class NtSource;

template <>
InputParameters validParams<NtSource>();

class NtSource : public Kernel
{
public:
  NtSource(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  const Real & _src;
};

#endif // NTSOURCE_H
