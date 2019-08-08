[GlobalParams]
  gravity = '0 -9.81 0'
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
    u = ux
    v = uy
    p = p
    component = 0
  [../]

  [./momentum_y]
    type = NSMomentum
    variable = uy
    u = ux
    v = uy
    p = p
    component = 1
  [../]
[]

[BCs]
  [./ux_dirichlet]
    type = DirichletBC
    variable = ux
    boundary = 'left bottom top'
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
    boundary = 'bottom'
    value = 1
  [../]

  [./p_right]
    type = DirichletBC
    variable = p
    boundary = 'top'
    value = 0
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    prop_names = 'rho mu'
    prop_values = '1. 1.'
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






