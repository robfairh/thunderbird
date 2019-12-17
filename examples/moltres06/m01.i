[Mesh]
  file = rectangle.msh
[]


[GlobalParams]
  num_groups = 2
  group_fluxes = 'flux1 flux2'
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


[Kernels]
  # Neutronics: Group1
  [./diff_group1]
    type = GroupDiffusion
    variable = flux1
    diffcoef = 1.0
    group_number = 1
  [../]

  [./sigma_r_group1]
    type = SigmaR
    variable = flux1
    rmxs = 1.0
    group_number = 1
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

  # Neutronics: Group2
  [./diff_group2]
    type = GroupDiffusion
    variable = flux2
    diffcoef = 1.0
    group_number = 2
  [../]

  [./inscatter_group2]
    type = InScatter
    variable = flux2
    gtransfxs = 1.0
    group_number = 2
  [../]

[]


[BCs]
  [./vacuum_flux1L]
    type = DirichletBC
    variable = flux1
    boundary = 'left'
    value = 0
  [../]
  [./vacuum_flux1R]
    type = DirichletBC
    variable = flux1
    boundary = 'right'
    value = 0
  [../]
  [./vacuum_flux2L]
    type = DirichletBC
    variable = flux2
    boundary = 'left'
    value = 0
  [../]
  [./vacuum_flux2R]
    type = DirichletBC
    variable = flux2
    boundary = 'right'
    value = 0
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