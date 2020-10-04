[Mesh]
  file = simple_cylinder.msh
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
[]

[BCs]

  [./right]
    type = DirichletBC
    variable = temperature
    boundary = 'coolant_top'
    value = 1
  [../]

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
