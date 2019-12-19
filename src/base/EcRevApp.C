#include "EcRevApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<EcRevApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

EcRevApp::EcRevApp(InputParameters parameters) : MooseApp(parameters)
{
  EcRevApp::registerAll(_factory, _action_factory, _syntax);
}

EcRevApp::~EcRevApp() {}

void
EcRevApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"EcRevApp"});
  Registry::registerActionsTo(af, {"EcRevApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
EcRevApp::registerApps()
{
  registerApp(EcRevApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
EcRevApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  EcRevApp::registerAll(f, af, s);
}
extern "C" void
EcRevApp__registerApps()
{
  EcRevApp::registerApps();
}
