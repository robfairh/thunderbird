[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 20.
  ymax = 20.
  nx = 40
  ny = 40
  elem_type = QUAD9
[]


[Variables]
  [./flux1]
    order = FIRST
    family = LAGRANGE
    initial_condition = 1
  [../]

[]


[Kernels]
  # Neutronics: Group1
  [./diff_group1]
    type = GroupDiffusion
    variable = flux1
    diffcoef = 1.0
  [../]

  [./sigma_r_group1]
    type = SigmaR
    variable = flux1
    remxs = 1.
  [../]

  [./source_1]
    #type = NtSource
    type = CoupledFissionKernel
    variable = flux1
    #nfxs = 10.
  [../]
[]


[BCs]
  [./vacuum_flux1]
    type = DirichletBC
    variable = flux1
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