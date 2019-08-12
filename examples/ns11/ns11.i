[GlobalParams]
  #gravity = '0 -9.81 0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 2.
  ymax = 1.
  nx = 20
  ny = 10
  elem_type = QUAD9
[]

[Variables]
  [./p]
    order = FIRST
    family = LAGRANGE
  [../]
  [./ux]
    order = SECOND
    family = LAGRANGE
  [../]
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
  [./mass]
    type = NSMass
    variable = p
    u = ux
    rho = rho
  [../]

  [./momentum_x]
    type = NSMomentum
    variable = ux
    u = ux
    rho = rho
    p = p
    component = 0
  [../]

  [./k_density]
    type = NSDensity
    variable = rho
    temp = temp
    temp_ref = 50
    beta = 1e-1
  [../]

  [./temp_advection]
    type = NSTemperature
    variable = temp
    u = 0
    v = 0
    rho = rho
  [../]
[]

[BCs]
  [./p_left]
    type = DirichletBC
    variable = p
    boundary = 'left'
    value = 100
  [../]
  [./p_right]
    type = DirichletBC
    variable = p
    boundary = 'right'
    value = 0
  [../]

  [./ux_dirichlet]
    type = DirichletBC
    variable = ux
    boundary = 'bottom top'
    value = 0
  [../]

  [./T_dirichlet1]
    type = DirichletBC
    variable = temp
    boundary = top
    value = 50
  [../]
  [./T_dirichlet2]
    type = DirichletBC
    variable = temp
    boundary = bottom
    value = 100
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    prop_names = 'rho_ref k cp mu'
    prop_values = '10. 1. 1. 1.'
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
  type = Steady
  petsc_options_iname = '-ksp_gmres_restart -pc_type -sub_pc_type -sub_pc_factor_levels'
  petsc_options_value = '300                bjacobi  ilu          4'
  line_search = none
  nl_rel_tol = 1e-12
  nl_max_its = 6
  l_tol = 1e-6
  l_max_its = 300
  #num_steps = 5
  #dt = 1
  #solve_type = 'PJFNK'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]