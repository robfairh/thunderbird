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
    diffcoef = 0.07
    block = 'fuel'
  [../]

  [./source]
    type = TempSource
    variable = temperature
    src = 10.0
    block = 'fuel'
  [../]

  [./diff_moderator]
    type = TempDiffusion
    variable = temperature
    diffcoef = 0.3
    block = 'moderator'
  [../]

  [./diff_reflector]
    type = TempDiffusion
    variable = temperature
    diffcoef = 0.004
    block = 'coolant'
  [../]

  [./advect]
    type = TempConvection
    variable = temperature
    rho = 1.0
    cp = 1.0
    velocity = '0.0 0.0 0.0'
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
  solve_type = 'PJFNK'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]