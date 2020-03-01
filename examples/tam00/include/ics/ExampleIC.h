#ifndef EXAMPLEIC_H
#define EXAMPLEIC_H

#include "InitialCondition.h"

class ExampleIC;
class Function;

template <>
InputParameters validParams<ExampleIC>();

class ExampleIC : public InitialCondition
{
public:
  ExampleIC(const InputParameters & parameters);

  virtual Real value(const Point & p) override;

private:
  Real _coefficient;
  const Function & _function;
};

#endif // EXAMPLEIC_H
