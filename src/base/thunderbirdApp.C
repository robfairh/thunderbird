#include "thunderbirdApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<thunderbirdApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

thunderbirdApp::thunderbirdApp(InputParameters parameters) : MooseApp(parameters)
{
  thunderbirdApp::registerAll(_factory, _action_factory, _syntax);
}

thunderbirdApp::~thunderbirdApp() {}

void
thunderbirdApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"thunderbirdApp"});
  Registry::registerActionsTo(af, {"thunderbirdApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
thunderbirdApp::registerApps()
{
  registerApp(thunderbirdApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
thunderbirdApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  thunderbirdApp::registerAll(f, af, s);
}
extern "C" void
thunderbirdApp__registerApps()
{
  thunderbirdApp::registerApps();
}
