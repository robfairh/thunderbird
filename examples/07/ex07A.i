[Mesh]
  file = rectangle.msh
[]

[Variables]
  [./temperature]
    order = FIRST
    family = LAGRANGE
  [../]
[]


[Kernels]
  [./temp_diffusion]
    type = TempDiffusion
    variable = temperature
  [../]
  [./temp_source]
    type = TempSource
    variable = temperature
  [../]
[]


[BCs]
  [./left]
    type = DirichletBC
    variable = temperature
    boundary = 'left'
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = temperature
    boundary = 'right'
    value = 0
  [../]
[]


[Materials]
  [./example]
    type = ExampleMaterial
    block = 'fuel'
    independent_vals = '0 20.0'
    dependent_vals = '1. 1.'
  [../]
[]


[Executioner]
  type = Steady
  solve_type = 'PJFNK'
  #num_steps = 50
  #dt = 1
[]


[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]