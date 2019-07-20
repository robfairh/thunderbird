[Mesh]
  # in this folder run ../../thunderbird-opt -i thunderbird.i
  file = rectangle.msh
[]

[Variables]
  [./flux]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = flux
  [../]

  [./conv]
    type = Convection
    variable = flux
    velocity = '0.0 1.0 0.0'
  [../]
[]

[BCs]
  [./bottom]
    type = DirichletBC
    variable = flux
    boundary = 'bottom'
    value = 0
  [../]

  [./left]
    type = DirichletBC
    variable = flux
    boundary = 'left'
    value = 1
  [../]

  [./right]
    type = DirichletBC
    variable = flux
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
