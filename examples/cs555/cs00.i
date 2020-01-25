[Mesh]
  file = two-chan.msh
[]

[Variables]
  [./temp]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  # Fuel
  [./TempDiffusionFuel]
    type = TempDiffusion
    variable = temp
    diffcoef = 0.0553
    #diffcoef = 1.0
    block = 'Fuel'
  [../]
  [./TempAdvectionFuel]
    type = TempConvection
    variable = temp
    rho = 2.146e-3
    #rho = 1.
    cp = 1967
    #cp = 1
    #velocity = '0 21.7 0'
    velocity = '0 21.7 0'
    block = 'Fuel'
  [../]
  [./TempSourceFuel]
    type = TempSource
    variable = temp
    src = 28
    #src = 1
    block = 'Fuel'
  [../]

  # Moderator
  [./TempDiffusionModerator]
    type = TempDiffusion
    variable = temp
    diffcoef = 0.312
    #diffcoef = 0.5
    block = 'Moderator'
  [../]
  [./TempSourceModerator]
    type = TempSource
    variable = temp
    src = 0.4032
    #src = 0.4
    block = 'Moderator'
  [../]
[]

[BCs]

  [./tempbottom]
    type = DirichletBC
    variable = temp
    boundary = 'Bottom r_R'
    value = 900.0
  [../]
[]

[Preconditioning]
  [./SMP_PJFNK]
    type = SMP
    full = true
    solve_type = PJFNK
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
  exodus = true
[]
