#Generic gtmhr 2D geometry

[Mesh]
  file = gtmhr-10-2d.msh
[]

[Variables]
  [./temperature]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./diff_fuel]
    type = TempDiffusion
    variable = temperature
    diffcoef = 7
    block = 'fuel'
  [../]

  [./source]
    type = TempSource
    variable = temperature
    src = 30.0e6
    block = 'fuel'
  [../]

  [./diff_moderator]
    type = TempDiffusion
    variable = temperature
    diffcoef = 30
    block = 'moderator'
  [../]

  [./diff_reflector]
    type = TempDiffusion
    variable = temperature
    diffcoef = 0.35
    block = 'coolant'
  [../]

  [./advect]
    type = TempConvection
    variable = temperature
    rho = 1.0
    cp = 5.2
    velocity = '0.0 90. 0.0'
    block = 'coolant'
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = temperature
    boundary = 'coolant_bottom'
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
  type = Steady
  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-6
  solve_type = 'NEWTON'
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type'
  petsc_options_value = 'lu       NONZERO'
  line_search = 'none'
  nl_max_its = 30
  l_max_its = 100
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]