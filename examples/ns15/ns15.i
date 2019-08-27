[GlobalParams]
  #gravity = '0 -9.81 0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 1.
  ymax = 2.
  nx = 10
  ny = 20
  elem_type = QUAD9
[]

[Variables]
  [./ux]
    order = SECOND
    family = LAGRANGE
    #initial_condition = 0
  [../]
  [./uy]
    order = SECOND
    family = LAGRANGE
    #initial_condition = -1.
  [../]
  [./p]
    order = FIRST
    family = LAGRANGE
  [../]
  [./rho]
    order = FIRST
    family = LAGRANGE
    #initial_condition = 1.
  [../]
  [./temp]
    order = SECOND
    family = LAGRANGE
    #initial_condition = 20.
  [../]
[]

[Kernels]
  #[./mass_time]
  #  type = NSTimeMass
  #  variable = rho
  #[../]

  [./mass]
    type = NSMass
    variable = rho
    u = ux
    v = uy
  [../]

  #[./x_momentum_time]
  #  type = NSTimeMomentum
  #  variable = ux
  #  rho = rho
  #  component = 0
  #[../]

  [./momentum_x]
    type = NSMomentum
    variable = ux
    u = ux
    v = uy
    p = p
    rho = rho
    component = 0
  [../]

  #[./y_momentum_time]
  #  type = NSTimeMomentum
  #  variable = uy
  #  rho = rho
  #  component = 1
  #[../]

  [./momentum_y]
    type = NSMomentum
    variable = uy
    u = ux
    v = uy
    p = p
    rho = rho
    component = 1
  [../]

  [./density]
    type = NSDensity
    variable = p
    rho = rho
    temp = temp
    bulk_m = 1e3
    p_ref = 100
    temp_ref = 100
    beta = 1e-3
  [../]

  #[./temperature_time]
  #  type = NSTimeTemperature
  #  variable = temp
  #  rho = rho
  #[../]

  [./temperature]
    type = NSTemperature
    variable = temp
    u = ux
    v = uy
    p = p
    rho = rho
  [../]
[]

[BCs]
  [./ux_dirichlet]
    type = DirichletBC
    variable = ux
    boundary = 'left bottom top right'
    value = 0
  [../]

  [./uy_dirichlet]
    type = DirichletBC
    variable = uy
    boundary = 'left right'
    value = 0
  [../]

  [./p_left]
    type = DirichletBC
    variable = p
    boundary = 'top'
    value = 20
  [../]

  [./rho_right]
    type = DirichletBC
    variable = rho
    boundary = 'top'
    value = 1.
  [../]

  #[./p_right]
  #  type = DirichletBC
  #  variable = p
  #  boundary = 'bottom'
  #  value = 10
  #[../]

  [./temp_right]
    type = DirichletBC
    variable = temp
    boundary = top
    value = 20
  [../]

  [./temp_left]
    type = DirichletBC
    variable = temp
    boundary = 'left right'
    value = 200
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    prop_names = 'rho_ref mu k cp'
    prop_values = '1. 1. 1. 1.'
  [../]
[]

[Preconditioning]
  [./SMP_PJFNK]
    type = SMP
    full = true
    solve_type = JFNK
  [../]
[]

[Executioner]
  type = Steady
  petsc_options_iname = '-ksp_gmres_restart -pc_type -sub_pc_type -sub_pc_factor_levels'
  petsc_options_value = '300                bjacobi  ilu          4'
  line_search = none
  nl_rel_tol = 1e-10
  nl_max_its = 6
  l_tol = 1e-6
  l_max_its = 300
  #num_steps = 5
  #dt = 0.01
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
