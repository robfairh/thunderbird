#ifndef NSTIMEMASS_H
#define NSTIMEMASS_H

#include "Kernel.h"

// Forward Declarations
class NSTimeMass;

template <>
InputParameters validParams<NSTimeMass>();

class NSTimeMass : public Kernel
{
public:
  NSTimeMass(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  //virtual Real computeQpJacobian();
  //virtual Real computeQpOffDiagJacobian(unsigned jvar);

  MooseVariable & _rho;
  const VariableValue & _rho_dot;


};

#endif // NSTIMEMASS_H
