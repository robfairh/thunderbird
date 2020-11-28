
[Mesh]
  type = GeneratedMesh
  dim = 1
  xmax = 200.
  nx = 400
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
  [./fission_source0]
    type = P3FissionEigenKernel
    variable = flux0
    second_flux = flux2
    chit = 1.0
    nsf = 0.004151858528265707
    val1 = 1
    val2 = -2
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
  [./fission_source1]
    type = P3FissionEigenKernel
    variable = flux2
    second_flux = flux0
    chit = 1.0
    nsf = 0.004151858528265707
    val1 = 0.8
    val2 = -0.4
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
  type = InversePowerMethod
  max_power_iterations = 150
  xdiff = 'group1diff'

  bx_norm = 'bnorm'
  k0 = 1.4
  pfactor = 1e-4
  l_max_its = 300

  # eig_check_tol = 1e-09
  sol_check_tol = 1e-08

  # solve_type = 'NEWTON'
  solve_type = 'JFNK'
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -sub_pc_type'
  petsc_options_value = 'asm lu'
[]

[Postprocessors]
  [./bnorm]
    type = ElmIntegTotFissNtsPostprocessor
    execute_on = linear
    first_flux = flux0
    second_flux = flux2
    nsf = 0.004151858528265707
  [../]
  [./group1diff]
    type = ElementL2Diff
    variable = flux0
    execute_on = 'linear timestep_end'
    use_displaced_mesh = false
  [../]
[]

[Outputs]
  perf_graph = true
  print_linear_residuals = true
  file_base = 'input-1g-crit'
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
    end_point = '200 0 0'
    sort_by = x
    num_points = 300
    execute_on = timestep_end
  [../]
[]
