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

  unsigned int _equation;
  unsigned int _group;
  const MaterialProperty<std::vector<Real>> & _couplexsA;
  const MaterialProperty<std::vector<Real>> & _couplexsB;

  std::vector<const VariableValue *> _flux0_groups;
  std::vector<unsigned int> _flux0_ids;

  std::vector<const VariableValue *> _flux2_groups;
  std::vector<unsigned int> _flux2_ids;
};

#endif // P3SIGMACOUPLED_H
