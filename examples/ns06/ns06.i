[GlobalParams]
  # gravity = '0 -9.81 0'
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
[]

[Kernels]
  [./mass]
    type = NSMass
    variable = p
    u = ux
    v = uy
  [../]

  [./momentum_x]
    type = NSMomentum
    variable = ux
    p = p
    component = 0
    mu = 0.1
  [../]

  [./momentum_y]
    type = NSMomentum
    variable = uy
    p = p
    component = 1
    mu = 0.1
  [../]
[]

[BCs]
  [./ux_dirichlet]
    type = DirichletBC
    variable = ux
    boundary = 'bottom top'
    value = 0
  [../]

  [./uy_dirichlet]
    type = DirichletBC
    variable = uy
    boundary = 'left right bottom top'
    value = 0
  [../]

  [./p_left]
    type = DirichletBC
    variable = p
    boundary = 'left'
    value = 1
  [../]

  [./p_right]
    type = DirichletBC
    variable = p
    boundary = 'right'
    value = 0
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
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]






