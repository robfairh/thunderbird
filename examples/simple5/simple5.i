[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 2.
  ymax = 1.
  nx = 20
  ny = 10
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
  [./u]
    order = SECOND
    family = LAGRANGE
  [../]

  [./v]
    order = SECOND
    family = LAGRANGE
  [../]

  [./rho]
    order = FIRST
    family = LAGRANGE
  [../]

  [./temp]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./p]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./momentum_x]
    type = NSMomentum
    variable = u
    u = u
    v = v
    rho = rho
    p = p
    component = 0
  [../]

  [./momentum_y]
    type = NSMomentum
    variable = v
    u = u
    v = v
    rho = rho
    p = p
    component = 1
  [../]
 
  [./mass]
    type = NSMass
    variable = rho
    u = u
    v = v
  [../]

  [./temperature]
    type = NSTemperature
    variable = temp
    u = u
    v = v
    p = p
    rho = rho
  [../]
[]

[AuxKernels]
  [./pressure]
    type = NSPressure
    variable = p
    rho = rho
    temp = temp
  [../]
[]

[BCs]
  [./ux_dirichlet_x1]
    type = DirichletBC
    variable = u
    boundary = 'left'
    value = 1
  [../]

  [./ux_dirichlet_y]
    type = DirichletBC
    variable = u
    boundary = 'bottom top'
    value = 0
  [../]

  [./temp_x1]
    type = DirichletBC
    variable = temp
    boundary = 'left'
    value = 40
  [../]

  [./temp_y]
    type = DirichletBC
    variable = temp
    boundary = 'top bottom'
    value = 50
  [../]

  [./rho_x1]
    type = DirichletBC
    variable = rho
    boundary = 'left'
    value = 1.
  [../]

  [./laplacian]
    type = INSMomentumNoBCBCLaplaceForm
    variable = u
    boundary = 'bottom top'
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    prop_names = 'mu k cp'
    prop_values = '1. 1. 1.'
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