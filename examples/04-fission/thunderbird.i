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
  [./diff]
    type = NtDiffusion
    variable = flux
    diffcoef = 2.0
  [../]

  [./abs]
    type = NtSigmaF
    variable = flux
    nu = 1.0
    xsf = 1.0
  [../]
[]

[BCs]
  [./left]
    type = DirichletBC
    variable = flux
    boundary = 'left'
    value = 0
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
