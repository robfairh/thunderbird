#ifndef ELMINTEGTOTFISSNTSPOSTPROCESSOR_H
#define ELMINTEGTOTFISSNTSPOSTPROCESSOR_H

#include "ElementIntegralPostprocessor.h"
#include "MooseVariableInterface.h"

// Forward Declarations
class ElmIntegTotFissNtsPostprocessor;

template <>
InputParameters validParams<ElmIntegTotFissNtsPostprocessor>();

class ElmIntegTotFissNtsPostprocessor : public ElementIntegralPostprocessor
/* public MooseVariableInterface */
{
public:
  ElmIntegTotFissNtsPostprocessor(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral() override;

  const VariableValue & _first_flux;
  const VariableValue & _second_flux;

  const Real & _nsf;
};

#endif
