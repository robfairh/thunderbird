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
  [./T]
    order = SECOND
    family = LAGRANGE
    initial_condition = 1
  [../]

  [./rho]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./mass_time]
    type = NSTimeMass
    variable = T
    rho = rho
  [../]

  [./mass_diff]
    type = Diffusion
    variable = T
  [../]

  [./rho_diff]
    type = Diffusion
    variable = rho
  [../]
[]

[BCs]
  [./T_dirichlet]
    type = DirichletBC
    variable = T
    boundary = 'left right'
    value = 0
  [../]

  [./rho_dirichlet]
    type = DirichletBC
    variable = rho
    boundary = 'left right'
    value = 0
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
  type = Transient
  petsc_options_iname = '-ksp_gmres_restart -pc_type -sub_pc_type -sub_pc_factor_levels'
  petsc_options_value = '300                bjacobi  ilu          4'
  line_search = none
  nl_rel_tol = 1e-10
  nl_max_its = 6
  l_tol = 1e-6
  l_max_its = 300
  num_steps = 5
  dt = 0.01
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
