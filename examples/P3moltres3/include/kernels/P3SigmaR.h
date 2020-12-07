#ifndef P3SIGMAR_H
#define P3SIGMAR_H

#include "Kernel.h"

class P3SigmaR;

template <>
InputParameters validParams<P3SigmaR>();

class P3SigmaR : public Kernel
{
public:
  P3SigmaR(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  unsigned int _equation;
  unsigned int _group;
  const MaterialProperty<std::vector<Real>> & _remxsA;
  const MaterialProperty<std::vector<Real>> & _remxsB;
};

#endif // P3SIGMAR_H