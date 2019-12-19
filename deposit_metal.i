[GlobalParams]
   vel_x = 0
   velocity = '${vel_x} 0.0 0.0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 200
  xmax = 1
[]

[Variables]
  [C_O]
    order = FIRST
    family = LAGRANGE
    [InitialCondition]
      type = FunctionIC
      function = C_O_IC_funtion
      variable = C_O
    []
  []
[]

[Kernels]
  [C_O_diff]
    type = MatDiffusion
    variable = C_O
    D_name = D_O
  []
  [C_O_dot]
    type = TimeDerivative
    variable = C_O
  []
  [C_O_con]
    type = ExampleConvection
    variable = C_O
  []
[]

[BCs]
  # For each equation, only two bcs are needed, if more then two bcs for each equation it will be over-specify. If nodalBC and integrateBC are applied at the same time,  nodalBC will be strongly enforced while integrateBC will be ignored.
  [C_O_right]
    type = DirichletBC
    variable = C_O
    boundary = 'right'
    value = 1
  []
  [C_O_left_theta]
    # C_O (primary var) will couple the value of C_R (coupled var)
    type = Theta
    variable = C_O
    boundary = 'left'
    coupled_var = '1'
    Exp = Exp_func
  []
[]

[Materials]
  [Diffusivity_of_C_O]
    type = GenericConstantMaterial
    prop_names = 'D_O'
    prop_values = '0.01'
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Transient
  num_steps = 20000
  solve_type = PJFNK
  end_time = '1.8'
  dtmax = '1e-4'
  line_search = basic
[]

[Outputs]
  # execute_on = 'TIMESTEP_END'
  # csv = true
  exodus = true
[]

[Debug]
  show_var_residual_norms = true
[]

[Functions]
  # #####parameter#####
  # #####parameter#####
  E1 = '1.4'
  v = '1'
  E0 = '1'
  end_time = '1.8'
  [Exp_func]
    type = ParsedFunction
    value = 'if(t<=(${end_time}/2), exp(n*F*(${E1}-${v}*t-${E0})/(R*T)), exp(n*F*(${E1}+${v}*t-${E0}-2*${v}*(${end_time}/2))/(R*T)))' # 6.2.2 time dependent
    vars = 'n F R T'
    vals = '1 96485 8.314 300'
  []
  [E]
    type = ParsedFunction
    value = 'if(t<=(${end_time}/2), ${E1}-${v}*t, ${E1}+${v}*t-2*${v}*(${end_time}/2))'
  []
  [C_O_IC_funtion]
    # Give C_O a small value to trigger the flux exchange
    type = ParsedFunction
    vars = 'a'
    value = 'a*x-a'
    vals = '-1E-9'
  []
[]

[Postprocessors]
  [C_O]
    type = NodalVariableValue
    nodeid = 0
    variable = C_O
  []
  [Flux_C_O]
    type = SideFluxIntegral
    diffusivity = D_O
    variable = 'C_O'
    boundary = 'left'
  []
  [E]
    type = FunctionValuePostprocessor
    function = E
  []
[]
