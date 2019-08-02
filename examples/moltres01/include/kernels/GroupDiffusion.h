#ifndef GROUPDIFFUSION_H
#define GROUPDIFFUSION_H

#include "Kernel.h"

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

  const Real & _diffcoef;
  unsigned int _group;
};

#endif // GROUPDIFFUSION_H
