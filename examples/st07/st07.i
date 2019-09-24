[GlobalParams]
  gravity = '0 -9.81 0'
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

[MeshModifiers]
  [./bottom_left]
    type = AddExtraNodeset
    new_boundary = center
    coord = '1 1'
  [../]
[]

[Variables]
  [./stress_y]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./eq_x]
    type = Equilibrium
    variable = stress_y
    component = 1
  [../]

  [./eq_x2]
    type = Equilibrium2
    variable = stress_y
    component = 1
  [../]
[]

[BCs]
  [./left1]
    type = DirichletBC
    #type = NeumannBC
    variable = stress_y
    boundary = 'top'
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
  nl_rel_tol = 1e-10
  nl_max_its = 12
  l_tol = 1e-6
  l_max_its = 300
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
