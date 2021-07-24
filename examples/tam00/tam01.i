[GlobalParams]
  gravity = '0 -9.8 0'
[]

[Mesh]
  [./generate]
    type = GeneratedMeshGenerator
    dim = 2
    xmax = 1.0
    ymax = 1.0
    nx = 20
    ny = 20
    elem_type = QUAD9
  []
  [./bottom_left]
    type = ExtraNodesetGenerator
    input = generate
    new_boundary = corner
    coord = '0 0'
  [../]
[]

[Variables]
  [./vel_x]
    order = SECOND
    family = LAGRANGE
  [../]
  [./vel_y]
    order = SECOND
    family = LAGRANGE
  [../]
  [./p]
    order = FIRST
    family = LAGRANGE
  [../]
  [./temp]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./mass]
    type = INSMass
    variable = p
    u = vel_x
    v = vel_y
    p = p
  [../]

  [./x_time_deriv]
    type = INSMomentumTimeDerivative
    variable = vel_x
  [../]
  [./y_time_deriv]
    type = INSMomentumTimeDerivative
    variable = vel_y
  [../]
  
  [./x_momentum_space]
    type = INSMomentumLaplaceForm
    variable = vel_x
    u = vel_x
    v = vel_y
    p = p
    component = 0
    integrate_p_by_parts = false
  [../]
  [./y_momentum_space]
    type = INSMomentumLaplaceForm
    variable = vel_y
    u = vel_x
    v = vel_y
    p = p
    component = 1
    integrate_p_by_parts = false
  [../]
  [./buoyancy_x]
    type = INSBoussinesqBodyForce
    variable = vel_x
    component = 0
    temperature = temp
    constant = 0
  [../]
  [./buoyancy_y]
    type = INSBoussinesqBodyForce
    variable = vel_y
    component = 1
    temperature = temp
    constant = 0
  [../]

  [./tempTimeDeriv]
    type = MatINSTemperatureTimeDerivative
    variable = temp
  [../]
  [./tempAdvectionDiffusion]
    type = INSTemperature
    variable = temp
    u = vel_x
    v = vel_y
  [../]
  [./tempSource]
    type = BodyForce
    variable = temp
    function = 'volsource'
  [../]
[]

[Functions]
  [./volsource]
    type = ParsedFunction
    value = 'sin( 3.141592 * x ) * sin( 3.141592 * y )'
  [../]
[]

[BCs]
  [./x_no_slip]
    type = DirichletBC
    variable = vel_x
    boundary = 'top bottom left right'
    value = 0.0
  [../]
  [./y_no_slip]
    type = DirichletBC
    variable = vel_y
    boundary = 'top bottom left right'
    value = 0.0
  [../]
  
  [./p_zero]
    type = DirichletBC
    boundary = corner
    variable = p
    value = 0
  [../]

  [./tempbc]
    type = DirichletBC
    variable = temp
    boundary = 'top bottom left right'
    value = 0
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    block = 0
    prop_names = 'rho mu    k     cp  alpha'
    prop_values = '1  1e-1  1e-3  1   1e-2'
  [../]
[]

[Preconditioning]
  [./SMP_PJFNK]
    type = SMP
    full = true
    solve_type = PJFNK
  [../]
[]

[Executioner]
  type = Transient
  end_time = 10

  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-6

  solve_type = 'NEWTON'
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type'
  petsc_options_value = 'lu       NONZERO'
  line_search = 'none'
  nl_max_its = 30
  l_max_its = 100

  dtmin = 1e-5
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1e-3
    cutback_factor = 0.4
    growth_factor = 1.2
    optimal_iterations = 20
  [../]
[]

[Outputs]
  #execute_on = 'timestep_end'
  exodus = true
[]
