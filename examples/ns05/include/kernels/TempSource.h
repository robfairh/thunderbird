#ifndef TEMPSOURCE_H
#define TEMPSOURCE_H

#include "Kernel.h"

class TempSource;

template <>
InputParameters validParams<TempSource>();

class TempSource : public Kernel
{
public:
  TempSource(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

  const Real & _src;
};

#endif // TEMPSOURCE_H
