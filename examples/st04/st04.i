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
  [./u]
    order = SECOND
    family = LAGRANGE
  [../]
[]


[Kernels]
  [./def1]
    type = Deformation
    variable = u
  [../]

  [./def2]
    type = Volumetric
    variable = u
    value = 4905
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = u
    boundary = 'left'
    value = 0
  [../]

  [./right] #value takes the value of sigma_x
    type = NeumannBC
    variable = u
    boundary = 'right'
    value = 9.81e3
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    prop_names = 'rho E nu'
    prop_values = '1700 10e9 0.14'
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
