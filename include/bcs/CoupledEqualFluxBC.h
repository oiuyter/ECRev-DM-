//* This file is revised from CoupledNeumannBC

#ifndef COUPLEDEQUALFLUXBC_H
#define COUPLEDEQUALFLUXBC_H

#include "IntegratedBC.h"

// Forward Declarations
class CoupledEqualFluxBC;

template <>
InputParameters validParams<CoupledEqualFluxBC>();

/**
 * Implements Neumann BC where grad(u)=-grad(v) on the boundary.
 */

class CoupledEqualFluxBC : public IntegratedBC
{
public:

  CoupledEqualFluxBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:

  const VariableGradient & _grad_couple_var;
  /// int label for coupled_var for Jac
  unsigned int _coupled_var_jac;
 /**
   * Diffusivity.
 */ 
  const MaterialProperty<Real> & _D_O;
 
};

#endif
