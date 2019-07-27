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
[]


[BCs]
  [./left]
    type = DirichletBC
    variable = temperature
    boundary = 'left'
    value = 1
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
    independent_vals = '0 0.25 0.5 0.75 1.0'
    dependent_vals = '1e-2 5e-3 1e-3 5e-3 1e-2'
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