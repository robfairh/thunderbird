[Mesh]
  file = rectangle.msh
[]


[GlobalParams]
  num_groups = 2
  num_precursor_groups = 6
  use_exp_form = false
  group_fluxes = 'group1 group2'
  #temperature = temp
  sss2_input = false
  pre_concs = 'pre1 pre2 pre3 pre4 pre5 pre6'
  account_delayed = false
[]


[Variables]
  [./group1]
    order = FIRST
    family = LAGRANGE
    #scaling = 1e4
  [../]
  [./group2]
    order = FIRST
    family = LAGRANGE
    #scaling = 1e4
  [../]
[]


[Kernels]
  # Neutronics: Group1
  [./diff_group1]
    type = GroupDiffusion
    variable = group1
    group_number = 1
  [../]

  [./sigma_r_group1]
    type = SigmaR
    variable = group1
    group_number = 1
  [../]

  [./inscatter_group1]
    type = InScatter
    variable = group1
    group_number = 1
  [../]

  [./source_1]
    type = NtSource
    variable = group1
    src = 1.0
  [../]

  # Neutronics: Group2
  [./diff_group2]
    type = GroupDiffusion
    variable = group2
    group_number = 2
  [../]

  [./sigma_r_group2]
    type = SigmaR
    variable = group2
    group_number = 2
  [../]

  [./inscatter_group2]
    type = InScatter
    variable = group2
    group_number = 2
  [../]

[]


[Materials]
  [./fuel]
    type = GenericMoltresMaterial
    property_tables_root = '../../property_file_dir/newt_msre_fuel_'
    interp_type = 'spline'
    #block = 'fuel'
    prop_names = 'k cp'
    prop_values = '.0553 1967' # Robertson MSRE technical report @ 922 K
  [../]
[]


[BCs]
  [./vacuum_flux1L]
    type = DirichletBC
    variable = group1
    boundary = 'left'
    value = 0
  [../]
  [./vacuum_flux1R]
    type = DirichletBC
    variable = group1
    boundary = 'right'
    value = 0
  [../]
  [./vacuum_flux2L]
    type = DirichletBC
    variable = group2
    boundary = 'left'
    value = 0
  [../]
  [./vacuum_flux2R]
    type = DirichletBC
    variable = group2
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