#Generic fuel-moderator-coolant 3D geometry

[Mesh]
  file = fuelmodcool3d.msh
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
    diffcoef = 1.0
    block = 'fuel'
  [../]

  [./source]
    type = TempSource
    variable = temperature
    src = 1.0
    block = 'fuel'
  [../]

  [./diff_moderator]
    type = TempDiffusion
    variable = temperature
    diffcoef = 1.0
    block = 'moderator'
  [../]

  [./diff_reflector]
    type = TempDiffusion
    variable = temperature
    diffcoef = 1.0
    block = 'coolant'
  [../]

  [./advect]
    type = TempConvection
    variable = temperature
    rho = 1.0
    cp = 1.0
    velocity = '0.0 1.0 0.0'
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

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]