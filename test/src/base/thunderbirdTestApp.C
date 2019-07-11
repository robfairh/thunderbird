//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "thunderbirdTestApp.h"
#include "thunderbirdApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<thunderbirdTestApp>()
{
  InputParameters params = validParams<thunderbirdApp>();
  return params;
}

thunderbirdTestApp::thunderbirdTestApp(InputParameters parameters) : MooseApp(parameters)
{
  thunderbirdTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

thunderbirdTestApp::~thunderbirdTestApp() {}

void
thunderbirdTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  thunderbirdApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"thunderbirdTestApp"});
    Registry::registerActionsTo(af, {"thunderbirdTestApp"});
  }
}

void
thunderbirdTestApp::registerApps()
{
  registerApp(thunderbirdApp);
  registerApp(thunderbirdTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
thunderbirdTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  thunderbirdTestApp::registerAll(f, af, s);
}
extern "C" void
thunderbirdTestApp__registerApps()
{
  thunderbirdTestApp::registerApps();
}
