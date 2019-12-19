//* This file is revised from MatchedValueBC

#ifndef THETA_H
#define THETA_H

#include "NodalBC.h"


// Forward Declarations
class Theta;
class Function;

template <>
InputParameters validParams<Theta>();

/**
 * Implements a simple coupled boundary condition where u=v on the boundary.
 */
class Theta : public NodalBC
{
public:
  Theta(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

  const VariableValue & _coupled_var;

  /// The id of the coupled variable
  unsigned int _coupled_var_num;


  /**
   * Evaluate the function at the current quadrature point and timestep.
   */
  Real f();

  Function & _func;

};

#endif // THETA_H
