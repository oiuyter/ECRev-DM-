//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#ifndef EC_REVTESTAPP_H
#define EC_REVTESTAPP_H

#include "MooseApp.h"

class EcRevTestApp;

template <>
InputParameters validParams<EcRevTestApp>();

class EcRevTestApp : public MooseApp
{
public:
  EcRevTestApp(InputParameters parameters);
  virtual ~EcRevTestApp();

  static void registerApps();
  static void registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs = false);
};

#endif /* EC_REVTESTAPP_H */
