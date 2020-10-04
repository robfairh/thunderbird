[Mesh]
  file = rectangle.msh
[]

[GlobalParams]
  num_groups = 2
  group_fluxes = 'flux1 flux2'
[]

[Variables]
  [./flux1]
    order = FIRST
    family = LAGRANGE
  [../]
  [./flux2]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  # Neutronics: Group1
  [./diff_group1]
    type = GroupDiffusion
    variable = flux1
    diffcoef = 1.0
    group_number = 1
  [../]
  [./sigma_r_group1]
    type = SigmaR
    variable = flux1
    rmxs = 1.0
    group_number = 1
  [../]
  [./inscatter_group1]
    type = InScatter
    variable = flux1
    gtransfxs = 0.0
    group_number = 1
  [../]
  [./source_1]
    type = NtSource
    variable = flux1
    src = 1.0
  [../]

  # Neutronics: Group2
  [./diff_group2]
    type = GroupDiffusion
    variable = flux2
    diffcoef = 1.0
    group_number = 2
  [../]
  [./inscatter_group2]
    type = InScatter
    variable = flux2
    gtransfxs = 1.0
    group_number = 2
  [../]
[]

[BCs]
  [./vacuum_flux1L]
    type = DirichletBC
    variable = flux1
    boundary = 'left right'
    value = 0
  [../]
  [./vacuum_flux2L]
    type = DirichletBC
    variable = flux2
    boundary = 'left right'
    value = 0
  [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  end_time = 100

  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-6

  solve_type = 'NEWTON'
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type'
  petsc_options_value = 'lu       NONZERO'
  line_search = 'none'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
  nl_max_its = 30
  l_max_its = 100
  dtmin = 1e-5
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1e-3
    cutback_factor = 0.4
    growth_factor = 1.2
    optimal_iterations = 20
  [../]
[]

[Outputs]
  #execute_on = 'timestep_end'
  exodus = true
[]