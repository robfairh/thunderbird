[Mesh]
  file = rectangle.msh
[]

[Variables]
  [./flux]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./abs]
    type = NtTimeDerivative
    variable = flux
    time_derivative_coeff = 1.0
  [../]
  
  [./diff]
    type = NtDiffusion
    variable = flux
    diffcoef = 2.0
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = flux
    boundary = 'bottom'
    value = 0
  [../]

  [./right]
    type = DirichletBC
    variable = flux
    boundary = 'top'
    value = 1
  [../]
[]

[Executioner]
  type = Transient
  solve_type = 'PJFNK'
  num_steps = 50
  dt = 1
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
