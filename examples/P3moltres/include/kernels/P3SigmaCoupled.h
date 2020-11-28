#ifndef P3SIGMACOUPLED_H
#define P3SIGMACOUPLED_H

#include "Kernel.h"

class P3SigmaCoupled;

template <>
InputParameters validParams<P3SigmaCoupled>();

class P3SigmaCoupled : public Kernel
{
public:
  P3SigmaCoupled(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Real & _val;

};

#endif // P3SIGMACOUPLED_H
