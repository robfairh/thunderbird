#ifndef CONVECTION_H
#define CONVECTION_H

#include "Kernel.h"

class Convection;

template <>
InputParameters validParams<Convection>();

class Convection : public Kernel
{
public:
  Convection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  RealVectorValue _velocity;
};

#endif // CONVECTION_H
