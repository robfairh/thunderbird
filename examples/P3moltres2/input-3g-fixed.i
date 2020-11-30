[GlobalParams]
  num_groups = 3
  num_precursor_groups = 8
  flux0_groups = 'flux0_1 flux0_2 flux0_3'
  flux2_groups = 'flux2_1 flux2_2 flux2_3'
[]

[Mesh]
  type = GeneratedMesh
  dim = 1
  xmax = 50.
  nx = 100
  elem_type = EDGE2
[]

[Variables]
  [./flux0_1]
    order = FIRST
    family = LAGRANGE
    initial_condition = 1
  [../]
  [./flux0_2]
    order = FIRST
    family = LAGRANGE
    initial_condition = 1
  [../]
  [./flux0_3]
    order = FIRST
    family = LAGRANGE
    initial_condition = 1
  [../]

  [./flux2_1]
    order = FIRST
    family = LAGRANGE
    initial_condition = 1
  [../]
  [./flux2_2]
    order = FIRST
    family = LAGRANGE
    initial_condition = 1
  [../]
  [./flux2_3]
    order = FIRST
    family = LAGRANGE
    initial_condition = 1
  [../]
[]

[Kernels]
  # Eq A group 1
  [./diff_flux0_1]
    type = P3Diffusion
    variable = flux0_1
    diffcoef = 1.83477519
  [../]
  [./sigma_r0_flux0_1]
    type = P3SigmaR
    variable = flux0_1
    remxs = 0.013903
  [../]
  [./sigma_r0_flux2_1]
    type = P3SigmaCoupled
    variable = flux0_1
    second_flux = flux2_1
    val = -0.027806
  [../]
  [./inscatter_flux1]
    type = P3InScatter
    variable = flux0_1
    group_number = 1
    val1 = 1
    val2 = -2
  [../]
  [./source0_1]
    type = BodyForce
    variable = flux0_1
    value = 1
  [../]

  # Eq A group 2
  [./diff_flux0_2]
    type = P3Diffusion
    variable = flux0_2
    diffcoef = 1.03382895
  [../]
  [./sigma_r0_flux0_2]
    type = P3SigmaR
    variable = flux0_2
    remxs = 0.005866
  [../]
  [./sigma_r0_flux2_2]
    type = P3SigmaCoupled
    variable = flux0_2
    second_flux = flux2_2
    val = -0.011732
  [../]
  [./inscatter_flux2]
    type = P3InScatter
    variable = flux0_2
    group_number = 2
    val1 = 1
    val2 = -2
  [../]

  # Eq A group 3
  [./diff_flux0_3]
    type = P3Diffusion
    variable = flux0_3
    diffcoef = 0.94602475
  [../]
  [./sigma_r0_flux0_3]
    type = P3SigmaR
    variable = flux0_3
    remxs = 0.015848
  [../]
  [./sigma_r0_flux2_3]
    type = P3SigmaCoupled
    variable = flux0_3
    second_flux = flux2_3
    val = -0.031696
  [../]
  [./inscatter_flux3]
    type = P3InScatter
    variable = flux0_3
    group_number = 3
    val1 = 1
    val2 = -2
  [../]

  # Eq B group 1
  [./diff_fluxB1]
    type = P3Diffusion
    variable = flux2_1
    diffcoef = 1.25180928
  [../]
  [./sigma_r1_flux21]
    type = P3SigmaR
    variable = flux2_1
    remxs = 0.21055927
  [../]
  [./sigma_r1_flux01]
    type = P3SigmaCoupled
    variable = flux2_1
    second_flux = flux0_1
    val = -0.0055612
  [../]
  [./inscatter_fluxB1]
    type = P3InScatter
    variable = flux2_1
    group_number = 1
    val1 = 0.8
    val2 = -0.4
  [../]
  [./sourceB]
    type = BodyForce
    variable = flux2_1
    value = -0.4
  [../]

  [./diff_fluxB2]
    type = P3Diffusion
    variable = flux2_2
    diffcoef = 0.75030232
  [../]
  [./sigma_r1_flux22]
    type = P3SigmaR
    variable = flux2_2
    remxs = 0.34688822
  [../]
  [./sigma_r1_flux02]
    type = P3SigmaCoupled
    variable = flux2_2
    second_flux = flux0_2
    val = -0.0023464
  [../]
  [./inscatter_fluxB2]
    type = P3InScatter
    variable = flux2_2
    group_number = 2
    val1 = 0.8
    val2 = -0.4
  [../]

  [./diff_fluxB3]
    type = P3Diffusion
    variable = flux2_3
    diffcoef = 0.69922674
  [../]
  [./sigma_r1_flux23]
    type = P3SigmaR
    variable = flux2_3
    remxs = 0.38063319
  [../]
  [./sigma_r1_flux03]
    type = P3SigmaCoupled
    variable = flux2_3
    second_flux = flux0_3
    val = -0.0063392
  [../]
  [./inscatter_fluxB3]
    type = P3InScatter
    variable = flux2_3
    group_number = 3
    val1 = 0.8
    val2 = -0.4
  [../]
[]

[BCs]
  [./vacuum_fluxA_1]
    type = P3VacuumBC
    boundary = 'left right'
    variable = flux0_1
    second_flux = flux2_1
    val1 = 0.5
    val2 = -0.75
  [../]
  [./vacuum_fluxA_2]
    type = P3VacuumBC
    boundary = 'left right'
    variable = flux0_2
    second_flux = flux2_2
    val1 = 0.5
    val2 = -0.75
  [../]
  [./vacuum_fluxA_3]
    type = P3VacuumBC
    boundary = 'left right'
    variable = flux0_3
    second_flux = flux2_3
    val1 = 0.5
    val2 = -0.75
  [../]

  [./vacuum_fluxB_1]
    type = P3VacuumBC
    boundary = 'left right'
    variable = flux2_1
    second_flux = flux0_1
    val1 = 0.525
    val2 = -0.075
  [../]
  [./vacuum_fluxB_2]
    type = P3VacuumBC
    boundary = 'left right'
    variable = flux2_2
    second_flux = flux0_2
    val1 = 0.525
    val2 = -0.075
  [../]
  [./vacuum_fluxB_3]
    type = P3VacuumBC
    boundary = 'left right'
    variable = flux2_3
    second_flux = flux0_3
    val1 = 0.525
    val2 = -0.075
  [../]
[]

[Materials]
  [./cross_sections]
    type = GenericMoltresMaterial
    property_tables_root = 'xs3g/'
    interp_type = 'linear'
  [../]
[]

# [Preconditioning]
#   [./SMP]
#     type = SMP
#     full = true
#   [../]
# []

[Executioner]
  type = Steady
  l_max_its = 100
  nl_abs_tol = 1e-5
  nl_max_its = 20

  # solve_type = 'NEWTON'
  # petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'
  # petsc_options_iname = '-pc_type -sub_ksp_type -snes_linesearch_minlambda'
  # petsc_options_value = 'lu       preonly       1e-3'

  solve_type = 'JFNK'
[]

[Outputs]
  perf_graph = true
  print_linear_residuals = true
  file_base = 'input-3g-fixed'
  execute_on = timestep_end
  exodus = true
  csv = true
[]

[Debug]
  show_var_residual_norms = true
[]

[VectorPostprocessors]
  [./line]
    type = LineValueSampler
    variable = 'flux0_1 flux0_2 flux0_3 flux2_1 flux2_2 flux2_3'
    start_point = '0 0 0'
    end_point = '50 0 0'
    sort_by = x
    num_points = 100
    execute_on = timestep_end
  [../]
[]
