#ifndef P3VACUUMBC_H
#define P3VACUUMBC_H

#include "IntegratedBC.h"

// Forward Declarations
class P3VacuumBC;

template <>
InputParameters validParams<P3VacuumBC>();

/**
 * Implements a simple VacuumConc BC for neutron diffusion on the boundary.
 * VacuumConc BC is defined as \f$ D\frac{du}{dn}+\frac{u}{2} = 0\f$, where u is neutron flux.
 * Hence, \f$ D\frac{du}{dn}=-\frac{u}{2} \f$ and \f$ -\frac{u}{2} \f$ is substituted into
 * the Neumann BC term produced from integrating the diffusion operator by parts.
 */
class P3VacuumBC : public IntegratedBC
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  P3VacuumBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  const VariableValue & _second_flux;
  const Real & _val1;
  const Real & _val2;

};

#endif // P3VACUUMBC_H
