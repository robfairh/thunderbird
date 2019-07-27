[Mesh]
  file = rectangle.msh
[]

flow_velocity = 1.0

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
    tempdiffcoef = 1.0
  [../]

  [./temp_advection_fuel]
    type = ConservativeTemperatureAdvection
    variable = temperature
    velocity = '0.0 ${flow_velocity} 0.0'
  [../]
[]


[BCs]
  [./bot]
    type = DirichletBC
    variable = temperature
    boundary = 'bottom'
    value = 0
  [../]
  [./temp_advection_outlet]
    type = TemperatureOutflowBC
    variable = temperature
    boundary = 'top'
    velocity = '0.0 ${flow_velocity} 0.0'
  [../]
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
    value = 1
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