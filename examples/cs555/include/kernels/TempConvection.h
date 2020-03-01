#ifndef TEMPCONVECTION_H
#define TEMPCONVECTION_H

#include "Kernel.h"

class TempConvection;

template <>
InputParameters validParams<TempConvection>();

class TempConvection : public Kernel
{
public:
  TempConvection(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  RealVectorValue _velocity;
  Real _rho;
  Real _cp;
};

#endif // TEMPCONVECTION_H
