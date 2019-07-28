#ifndef COUPLEDFISSIONKERNEL_H
#define COUPLEDFISSIONKERNEL_H

#include "Kernel.h"

// Forward Declarations
class CoupledFissionKernel;

template <>
InputParameters validParams<CoupledFissionKernel>();

/**
 * Computes fission source of neutrons without normalizing by
 * \f$ 1/k \f$. Note that this kernel is meant for transients.
 */
class CoupledFissionKernel : public Kernel
{
public:
  CoupledFissionKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  
  const MaterialProperty<std::vector<Real>> & _nsf;
  const MaterialProperty<std::vector<Real>> & _d_nsf_d_temp;
  const MaterialProperty<std::vector<Real>> & _chi;
  const MaterialProperty<std::vector<Real>> & _d_chi_d_temp;
  const MaterialProperty<Real> & _beta;
  const MaterialProperty<Real> & _d_beta_d_temp;
  unsigned int _group;
  unsigned int _num_groups;
  unsigned int _temp_id;
  const VariableValue & _temp;
  std::vector<const VariableValue *> _group_fluxes;
  std::vector<unsigned int> _flux_ids;
  bool _account_delayed;
};

#endif // COUPLEDFISSIONKERNEL_H
