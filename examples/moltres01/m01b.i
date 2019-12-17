[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 1.
  ymax = 2.
  nx = 10
  ny = 10
  elem_type = QUAD9
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
    rmxs = 0.17
    group_number = 1
  [../]

  [./fission_source_group1]
    type = CoupledFissionKernel
    variable = flux1
    group_number = 1
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
  [./vacuum_flux1]
    type = DirichletBC
    variable = flux1
    boundary = 'left right'
    value = 0
  [../]
  [./vacuum_flux2]
    type = DirichletBC
    variable = flux2
    boundary = 'left right'
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