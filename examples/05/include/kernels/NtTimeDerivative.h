#ifndef NTTIMEDERIVATIVE_H
#define NTTIMEDERIVATIVE_H

#include "TimeDerivative.h"

// Forward Declaration
class NtTimeDerivative;

template <>
InputParameters validParams<NtTimeDerivative>();

class NtTimeDerivative : public TimeDerivative
{
public:
  NtTimeDerivative(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

  Real _time_derivative_coeff;
};

#endif // NTTIMEDERIVATIVE_H