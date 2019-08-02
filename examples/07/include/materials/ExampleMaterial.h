#ifndef EXAMPLEMATERIAL_H
#define EXAMPLEMATERIAL_H

#include "Material.h"
#include "LinearInterpolation.h"

class ExampleMaterial;

template <>
InputParameters validParams<ExampleMaterial>();

class ExampleMaterial : public Material
{
public:
  ExampleMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties() override;

private:
  const VariableValue & _temperature;
  MaterialProperty<Real> & _diffusivity;
  LinearInterpolation _piecewise_func;
};

#endif // EXAMPLEMATERIAL_H