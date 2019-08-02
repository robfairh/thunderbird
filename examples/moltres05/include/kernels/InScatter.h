#ifndef INSCATTER_H
#define INSCATTER_H

#include "Kernel.h"

// Forward Declaration
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

  const MaterialProperty<std::vector<Real>> & _gtransfxs;
  const MaterialProperty<std::vector<Real>> & _d_gtransfxs_d_temp;
  unsigned int _group;
  unsigned int _num_groups;
  unsigned int _temp_id;
  std::vector<const VariableValue *> _group_fluxes;
  std::vector<unsigned int> _flux_ids;
  bool _sss2_input;
};

#endif // INSCATTER_H
