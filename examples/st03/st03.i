[GlobalParams]
  gravity = '9.81 9.81 0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 2.
  ymax = 2.
  nx = 20
  ny = 20
  elem_type = QUAD9
[]

[Variables]
  [./stress]
    order = FIRST
    family = LAGRANGE
  [../]

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./strain]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./eq_x]
    type = Equilibrium
    variable = stress
    component = 0
  [../]

  [./defor]
    type = Deformation
    variable = u
    strain_x = strain
  [../]
[]

[AuxKernels]
  [./const_x]
    type = AuxConstitutive
    variable = strain
    sigma_x = stress
    E = 10e9
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = stress
    boundary = 'left'
    value = 0
  [../]

  [./right]
    type = DirichletBC
    variable = u
    boundary = 'left'
    value = 0
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    prop_names = 'rho nu'
    prop_values = '1700 0.14'
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
