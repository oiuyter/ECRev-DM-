//* This file is is revised from CoupledNeumannBC, C_R take the flux from C_O


#include "CoupledEqualFluxBC.h"

registerMooseObject("EcRevApp", CoupledEqualFluxBC);

template <>
InputParameters
validParams<CoupledEqualFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addCoupledVar("coupled_var", "Coupled the variable C_O.");
  
  params.addParam<MaterialPropertyName>("D_O","D_O", "Diffusivity for oxidizing agent.");
  params.addParam<MaterialPropertyName>("D_R","D_R", "Diffusivity for reducing agent.");
  return params;
}

CoupledEqualFluxBC::CoupledEqualFluxBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _grad_couple_var(coupledGradient("coupled_var")),
    _coupled_var_jac(coupled("coupled_var")),
    _D_O(getMaterialProperty<Real>("D_O"))

{
}


Real
CoupledEqualFluxBC::computeQpResidual()
{
    return  _test[_i][_qp] *_grad_couple_var[_qp] * _D_O[_qp] *_normals[_qp];
}

//This will improve convergence
Real
CoupledEqualFluxBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _coupled_var_jac)
    return _test[_i][_qp] *_grad_phi[_j][_qp] * _D_O[_qp]*_normals[_qp];
  else
    return 0.;
}

