#ifndef GROUPDIFFUSION_H
#define GROUPDIFFUSION_H

#include "Kernel.h"

// Forward Declaration
class GroupDiffusion;

template <>
InputParameters validParams<GroupDiffusion>();

class GroupDiffusion : public Kernel
{
public:
  GroupDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const MaterialProperty<std::vector<Real>> & _diffcoef;
  const MaterialProperty<std::vector<Real>> & _d_diffcoef_d_temp;
  unsigned int _group;
  unsigned int _temp_id;
};

#endif // GROUPDIFFUSION_H
