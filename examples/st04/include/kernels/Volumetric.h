#ifndef VOLUMETRIC_H
#define VOLUMETRIC_H

#include "Kernel.h"

class Volumetric;

template <>
InputParameters validParams<Volumetric>();

class Volumetric : public Kernel
{
public:
  Volumetric(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  const Real & _value;

};

#endif // VOLUMETRIC_H
