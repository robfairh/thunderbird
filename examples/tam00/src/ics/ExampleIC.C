#include "ExampleIC.h"
#include "Function.h"

registerMooseObject("ExampleApp", ExampleIC);

template <>
InputParameters
validParams<ExampleIC>()
{
  InputParameters params = validParams<InitialCondition>();
  params.addRequiredParam<Real>("coefficient", "A constant that multiplies the initial condition");
  params.addParam<FunctionName>("function", "1", "A function that describes the initial condition");
  return params;
}

ExampleIC::ExampleIC(const InputParameters & parameters)
  : InitialCondition(parameters),
   _coefficient(getParam<Real>("coefficient")),
   _function(getFunction("function"))
{
}

Real
ExampleIC::value(const Point & p)
{
  // The Point class is defined in libMesh.  The spatial coordinates x,y,z can be accessed
  // individually using the parenthesis operator and a numeric index from 0..2
  return  _coefficient * _function.value(_t, p);
}
