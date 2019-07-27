[Mesh]
  file = rectangle.msh
[]

[Variables]
  [./flux1]
    order = FIRST
    family = LAGRANGE
  [../]
  [./flux2]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[GlobalParams]
  group_fluxes = 'flux1 flux2'
  num_groups = 2
[]

[Kernels]
  [./diff1]
    type = NtDiffusion
    variable = flux1
    diffcoef = 2.0
  [../]

  [./inscatter_group1]
    type = InScatter
    variable = flux1
    gtransfxs = 0.0
    group_number = 1
  [../]

  [./source_1]
    type = NtSource
    variable = flux1
    src = 1.0
  [../]

  [./diff2]
    type = NtDiffusion
    variable = flux2
    diffcoef = 2.0
  [../]

  [./inscatter_group2]
    type = InScatter
    variable = flux2
    gtransfxs = 1.0
    group_number = 2
  [../]

[]

[BCs]
  [./flux1L]
    type = DirichletBC
    variable = flux1
    boundary = 'left'
    value = 0
  [../]

  [./flux1R]
    type = DirichletBC
    variable = flux1
    boundary = 'right'
    value = 0
  [../]

  [./left2L]
    type = DirichletBC
    variable = flux2
    boundary = 'left'
    value = 0
  [../]

  [./right2R]
    type = DirichletBC
    variable = flux2
    boundary = 'right'
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
