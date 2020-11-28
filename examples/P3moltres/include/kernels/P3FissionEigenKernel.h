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

  const VariableValue & _second_flux;
  const Real & _chi_t;
  const Real & _nsf;
  const Real & _val1;
  const Real & _val2;

};

#endif // COUPLEDFISSIONEIGENKERNEL_H
