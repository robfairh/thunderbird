#ifndef P3FISSIONEIGENKERNEL_H
#define P3FISSIONEIGENKERNEL_H

#include "EigenKernel.h"

// Forward Declarations
class P3FissionEigenKernel;

template <>
InputParameters validParams<P3FissionEigenKernel>();

/**
 * Computes the fission source normalized by eigenvalue. In other words:
 * \f[
 *   \frac{1}{k} \sum_g \nu \Sigma_{g,f} \phi_g
 * \f]
 */
class P3FissionEigenKernel : public EigenKernel
{
public:
  P3FissionEigenKernel(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  unsigned int _equation;
  unsigned int _group;
  unsigned int _num_groups;
  const MaterialProperty<std::vector<Real>> & _nsf;
  const MaterialProperty<std::vector<Real>> & _chi_t;

  std::vector<const VariableValue *> _flux0_groups;
  std::vector<unsigned int> _flux0_ids;

  std::vector<const VariableValue *> _flux2_groups;
  std::vector<unsigned int> _flux2_ids;
  
};

#endif // COUPLEDFISSIONEIGENKERNEL_H
