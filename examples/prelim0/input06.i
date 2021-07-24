[GlobalParams]
  gravity = '0 -9.8 0'
[]

[Mesh]
  file = geom05.msh
[]

[Variables]
  [./vel_x]
    order = SECOND
    family = LAGRANGE
    block = 'room'
  [../]
  [./vel_y]
    order = SECOND
    family = LAGRANGE
    block = 'room'
  [../]
  [./p]
    order = FIRST
    family = LAGRANGE
    block = 'room'
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
    block = 'room'
  [../]

  [./x_time_deriv]
    type = INSMomentumTimeDerivative
    variable = vel_x
    block = 'room'
  [../]
  [./y_time_deriv]
    type = INSMomentumTimeDerivative
    variable = vel_y
    block = 'room'
  [../]
  [./x_momentum_space]
    type = INSMomentumLaplaceForm
    variable = vel_x
    u = vel_x
    v = vel_y
    p = p
    component = 0
    integrate_p_by_parts = false
    block = 'room'
  [../]
  [./y_momentum_space]
    type = INSMomentumLaplaceForm
    variable = vel_y
    u = vel_x
    v = vel_y
    p = p
    component = 1
    integrate_p_by_parts = false
    block = 'room'
  [../]
  [./buoyancy_x]
    type = INSBoussinesqBodyForce
    variable = vel_x
    component = 0
    temperature = temp
    constant = 0
    block = 'room'
  [../]
  [./buoyancy_y]
    type = INSBoussinesqBodyForce
    variable = vel_y
    component = 1
    temperature = temp
    constant = 0
    block = 'room'
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
    block = 'room'
  [../]
  [./source_diff]
    type = Diffusion
    variable = temp
    block = 'source'
  [../]
  [./tempSource]
    type = BodyForce
    variable = temp
    function = 'heat_source'
    block = 'source'
  [../]
[]

[Functions]
  [./heat_source]
    type = PiecewiseLinear
    data_file = 'heat_source.csv'
    format = columns
    xy_in_file_only = True
    # x_index_in_file = 1
    # y_index_in_file = 2
  [../]
[]

[BCs]
  [./x_no_slip]
    type = DirichletBC
    variable = vel_x
    boundary = 'top bottom left right source_wall'
    value = 0.0
  [../]
  [./y_no_slip]
    type = DirichletBC
    variable = vel_y
    boundary = 'top bottom left right source_wall'
    value = 0.0
  [../]
  
  [./p_zero]
    type = DirichletBC
    boundary = corner
    variable = p
    value = 0
  [../]

  [./tempbc1]
    type = DirichletBC
    variable = temp
    boundary = 'top bottom left right'
    value = 0.0
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    # block = 0
    prop_names = 'rho mu    k     cp  alpha'
    prop_values = '1  1e-1  1e-3  1   1e-2'
  [../]
[]

[Preconditioning]
  [./SMP_PJFNK]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  end_time = 50

  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-6

  solve_type = 'NEWTON'
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'
  # petsc_options_iname = '-pc_type -pc_factor_shift_type'
  # petsc_options_value = 'lu       NONZERO'
  petsc_options_iname = '-pc_type -sub_pc_type -pc_factor_shift_type'
  petsc_options_value = 'lu       lu           NONZERO'
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
  file_base = 'input06'
  exodus = true
[]
