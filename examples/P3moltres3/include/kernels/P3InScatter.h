#ifndef P3INSCATTER_H
#define P3INSCATTER_H

#include "Kernel.h"

// Forward Declaration
class P3InScatter;

template <>
InputParameters validParams<P3InScatter>();

class P3InScatter : public Kernel
{
public:
  P3InScatter(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  unsigned int _group;
  unsigned int _num_groups;
  const MaterialProperty<std::vector<Real>> & _gtransfxs;

  std::vector<const VariableValue *> _flux0_groups;
  std::vector<unsigned int> _flux0_ids;

  std::vector<const VariableValue *> _flux2_groups;
  std::vector<unsigned int> _flux2_ids;
  
  const Real & _val1;
  const Real & _val2;
};

#endif // P3INSCATTER_H
