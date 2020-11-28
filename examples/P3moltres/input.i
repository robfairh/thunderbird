
[Mesh]
  type = GeneratedMesh
  dim = 1
  xmax = 5.
  nx = 100
  elem_type = EDGE2
[]

[Variables]
  [./flux0]
    order = FIRST
    family = LAGRANGE
    initial_condition = 1
  [../]
  [./flux2]
    order = FIRST
    family = LAGRANGE
    initial_condition = 1
  [../]
[]

[Kernels]
  [./diff_flux0]
    type = P3Diffusion
    variable = flux0
    diffcoef = 1.1204649917687304
  [../]
  [./sigma_r0_flux0]
    type = P3SigmaR
    variable = flux0
    remxs = 0.0036538102433835706
  [../]
  [./sigma_r0_flux2]
    type = P3SigmaCoupled
    variable = flux0
    second_flux = flux2
    val = -0.007307620486767141
  [../]
  [./source0]
    type = BodyForce
    variable = flux0
    value = 1
  [../]

  [./diff_flux1]
    type = P3Diffusion
    variable = flux2
    diffcoef = 0.8128104526665887
  [../]
  [./sigma_r1_flux2]
    type = P3SigmaR
    variable = flux2
    remxs = 0.3178407885712954
  [../]
  [./sigma_r1_flux0]
    type = P3SigmaCoupled
    variable = flux2
    second_flux = flux0
    val = -0.0014615240973534283
  [../]
  [./source1]
    type = BodyForce
    variable = flux2
    value = -0.4
  [../]
[]

[BCs]
  [./vacuum_flux0]
    type = P3VacuumBC
    boundary = 'left right'
    variable = flux0
    second_flux = flux2
    val1 = 0.5
    val2 = -0.75
  [../]

  [./vacuum_flux2]
    type = P3VacuumBC
    boundary = 'left right'
    variable = flux2
    second_flux = flux0
    val1 = 0.525
    val2 = -0.075
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
  file_base = 'input'
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
    variable = 'flux0 flux2'
    start_point = '0 0 0'
    end_point = '5 0 0'
    sort_by = x
    num_points = 100
    execute_on = timestep_end
  [../]
[]
