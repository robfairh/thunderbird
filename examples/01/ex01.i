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
  [./diff]
    type = Diffusion
    variable = temperature
  [../]

  [./conv]
    type = Convection
    variable = temperature
    velocity = '0.0 1.0 0.0'
  [../]
[]

[BCs]
  [./bottom]
    type = DirichletBC
    variable = temperature
    boundary = 'bottom'
    value = 0
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
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
