[GlobalParams]
  gravity = '0 -9.81 0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = .05
  ymax = .05
  nx = 20
  ny = 20
  elem_type = QUAD9
[]

[MeshModifiers]
  [./bottom_left]
    type = AddExtraNodeset
    new_boundary = corner
    coord = '0 0'
  [../]
[]

[Variables]
  [./ux]
    order = SECOND
    family = LAGRANGE
  [../]
  [./uy]
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
    initial_condition = 200
    scaling = 1e-4
  [../]
[]

[Kernels]
  [./mass]
    type = INSMass
    variable = p
    u = ux
    v = uy
    p = p
  [../]
  [./x_time_deriv]
    type = INSMomentumTimeDerivative
    variable = ux
  [../]
  [./y_time_deriv]
    type = INSMomentumTimeDerivative
    variable = uy
  [../]
  [./x_momentum_space]
    type = INSMomentumLaplaceForm
    variable = ux
    u = ux
    v = uy
    p = p
    component = 0
    integrate_p_by_parts = false
  [../]
  [./y_momentum_space]
    type = INSMomentumLaplaceForm
    variable = uy
    u = ux
    v = uy
    p = p
    component = 1
    integrate_p_by_parts = false
  [../]
  [./buoyancy_x]
    type = INSBoussinesqBodyForce
    variable = ux
    component = 0
    temperature = temp
    constant = 900
  [../]
  [./buoyancy_y]
    type = INSBoussinesqBodyForce
    variable = uy
    component = 1
    temperature = temp
    constant = 200
  [../]
  [./tempTimeDeriv]
    type = MatINSTemperatureTimeDerivative
    variable = temp
  [../]
  [./tempAdvectionDiffusion]
    type = INSTemperature
    variable = temp
    u = ux
    v = uy
  [../]
[]

[BCs]
  [./ux_dirichlet]
    type = DirichletBC
    variable = ux
    boundary = 'left right bottom top'
    value = 0
  [../]
  [./uy_dirichlet]
    type = DirichletBC
    variable = uy
    boundary = 'left right bottom top'
    value = 0
  [../]
  [./p_zero]
    type = DirichletBC
    boundary = corner
    variable = p
    value = 0
  [../]
  [./temp_insulate]
    type = NeumannBC
    variable = temp
    value = 0 # no conduction through side walls
    boundary = 'top bottom right' # not top
  [../]
  [./coldOnTop]
    type = DirichletBC
    variable = temp
    boundary = left
    value = 300
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    # alpha = coefficient of thermal expansion where rho  = rho0 -alpha * rho0 * delta T
    prop_names = 'mu rho alpha k cp'
    prop_values = '30.74e-6 .5757 2.9e-3 46.38e-3 1054'
  [../]
[]

[Preconditioning]
  [./Newton_SMP]
    type = SMP
    full = true
    solve_type = 'NEWTON'
  [../]
[]

[Executioner]
  type = Transient
  num_steps = 5
  dt = 0.01
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_test_display'
  petsc_options_iname = '-pc_type -pc_factor_shift_type -pc_factor_shift_amount'
  petsc_options_value = 'lu	  NONZERO		1e-10'
  line_search = 'none'
  nl_rel_tol = 1e-12
  nl_max_its = 20
  l_tol = 1e-6
  l_max_its = 300
  dtmin = 1e-5
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]






