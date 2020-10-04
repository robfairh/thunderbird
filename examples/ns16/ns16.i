[GlobalParams]
  #gravity = '0 -9.81 0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 1.
  ymax = 2.4
  nx = 10
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
    variable = rho
    u = ux
    v = uy
  [../]
  [./momentum_x]
    type = NSMomentum
    variable = ux
    u = ux
    v = uy
    rho = rho
    temp = temp
    component = 0
  [../]
  [./momentum_y]
    type = NSMomentum
    variable = uy
    u = ux
    v = uy
    rho = rho
    temp = temp
    component = 1
  [../]
  [./temp_advection]
    type = NSTemperature
    variable = temp
    u = ux
    v = uy
    rho = rho
  [../]
[]

[BCs]
  [./ux_dirichlet_y]
    # ??
    type = DirichletBC
    variable = ux
    boundary = 'bottom top'
    value = 0
  [../]

  [./ux_dirichlet_x]
    # This one should be correct
    type = DirichletBC
    variable = ux
    boundary = 'left right'
    value = 0
  [../]

  [./uy_dirichlet_x]
    # This one is correct
    type = DirichletBC
    variable = uy
    boundary = 'left right'
    value = 0
  [../]

  #[./uy_dirichlet_y]
    # ??
  #  type = DirichletBC
  #  variable = uy
  #  boundary = 'bottom'
  #  value = 1.
  #[../]

  [./T_dirichlet_x]
    # symmetry
    type = DirichletBC
    variable = temp
    boundary = 'left right'
    value = 100
  [../]

  [./T_dirichlet_y]
    # ??
    type = DirichletBC
    variable = temp
    boundary = bottom
    value = 50
  [../]

  [./rho_dirichlet_xy]
    # Maybe
    type = DirichletBC
    variable = rho
    boundary = corner
    value = 1
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    prop_names = 'R mu cv k'
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
  nl_rel_tol = 1e-12
  nl_max_its = 6
  l_tol = 1e-6
  l_max_its = 300
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]