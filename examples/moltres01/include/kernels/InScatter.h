#ifndef INSCATTER_H
#define INSCATTER_H

#include "Kernel.h"

class InScatter;

template <>
InputParameters validParams<InScatter>();

class InScatter : public Kernel
{
public:
  InScatter(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const Real & _gtransfxs;
  unsigned int _group;
  unsigned int _num_groups;
  std::vector<const VariableValue *> _group_fluxes;
  std::vector<unsigned int> _flux_ids;
};

#endif // INSCATTER_H
