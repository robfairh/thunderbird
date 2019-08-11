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
  #[./p]
  #  order = FIRST
  #  family = LAGRANGE
  #[../]
  #[./ux]
  #  order = SECOND
  #  family = LAGRANGE
  #[../]
  #[./uy]
  #  order = SECOND
  #  family = LAGRANGE
  #[../]
  [./rho]
    order = SECOND
    family = LAGRANGE
  [../]
  [./temp]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[Kernels]
  #[./mass]
  #  type = NSMass
  #  variable = p
  #  u = ux
  #  v = uy
  #  rho = rho
  #[../]

  #[./x_time_deriv]
  #  type = NSMomentumTimeDerivative
  #  variable = ux
  #  rho = rho
  #[../]
  #[./y_time_deriv]
  #  type = NSMomentumTimeDerivative
  #  variable = uy
  #  rho = rho
  #[../]
  #[./momentum_x]
  #  type = NSMomentum
  #  variable = ux
  #  u = ux
  #  v = uy
  #  rho = rho
  #  p = p
  #  component = 0
  #[../]
  #[./momentum_y]
  #  type = NSMomentum
  #  variable = uy
  #  u = ux
  #  v = uy
  #  rho = rho
  #  p = p
  #  component = 1
  #[../]

  [./k_density]
    type = NSDensity
    variable = rho
    #p = p
    temp = temp
    p_ref = 50
    temp_ref = 50
    bulk_m = 1e6
    beta = 10.0
  [../]

  #[./temp_time]
  #  type = MatINSTemperatureTimeDerivative
  #  variable = temp
  #  rho = rho
  #[../]
  [./temp_advection]
    type = NSTemperature
    variable = temp
    u = 0
    v = 0
    rho = rho
  [../]
  #[./temp_vd]
  #  type = NSTemperatureVD
  #  variable = temp
  #  u = ux
  #  v = uy
  #[../]
[]

[BCs]
  #[./p_left]
  #  type = DirichletBC
  #  variable = p
  #  boundary = 'bottom'
  #  value = 0
  #[../]

  #[./p_right]
  #  type = DirichletBC
  #  variable = p
  #  boundary = 'top'
  #  value = 100
  #[../]

  #[./ux_dirichlet]
  #  type = DirichletBC
  #  variable = ux
  #  boundary = 'left bottom top'
  #  value = 0
  #[../]

  #[./uy_dirichlet]
  #  type = DirichletBC
  #  variable = uy
  #  boundary = 'left right'
  #  value = 0
  #[../]

  [./T_dirichlet]
    type = DirichletBC
    variable = temp
    boundary = 'bottom'
    value = 100
  [../]

  [./T_top]
    type = DirichletBC
    variable = temp
    boundary = top
    value = 50
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    prop_names = 'rho_ref mu cp k'
    prop_values = '10. 1. 1. 1.'
  [../]
[]

#[Preconditioning]
#  [./SMP_PJFNK]
#    type = SMP
#    full = true
#    solve_type = PJFNK
#  [../]
#[]

[Executioner]
  type = Steady
  #petsc_options_iname = '-ksp_gmres_restart -pc_type -sub_pc_type -sub_pc_factor_levels'
  #petsc_options_value = '300                bjacobi  ilu          4'
  #line_search = none
  #nl_rel_tol = 1e-12
  #nl_max_its = 6
  #l_tol = 1e-6
  #l_max_its = 300
  #num_steps = 5
  #dt = 1
  solve_type = 'PJFNK'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]