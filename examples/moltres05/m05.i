[Mesh]
  file = rectangle.msh
[]

flow_velocity = 1.e-2
nt_scale = 5e12

[GlobalParams]
  num_groups = 2
  num_precursor_groups = 6
  use_exp_form = false
  group_fluxes = 'group1 group2'
  temperature = temp
  sss2_input = false
  pre_concs = 'pre1 pre2 pre3 pre4 pre5 pre6'
  account_delayed = false
[]


[Variables]
  [./group1]
    order = FIRST
    family = LAGRANGE
    #scaling = 1e4
    #initial_condition = 1
  [../]
  [./group2]
    order = FIRST
    family = LAGRANGE
    #scaling = 1e4
    #initial_condition = 1
  [../]
  [./temp]
    order = FIRST
    family = LAGRANGE
    initial_condition = 700
    #scaling = 1e-4
  [../]
[]


[Kernels]
  # Neutronics: Group1
  [./time_group1]
    type = NtTimeDerivative
    variable = group1
    group_number = 1
  [../]
  
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

  [./fission_source_group1]
    type = CoupledFissionKernel
    variable = group1
    group_number = 1
    #block = 'fuel'
  [../]

  [./source_1]
    type = NtSource
    variable = group1
    src = 1.0
  [../]

  [./time_group2]
    type = NtTimeDerivative
    variable = group2
    group_number = 2
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

  [./fission_source_group2]
    type = CoupledFissionKernel
    variable = group2
    group_number = 2
    #block = 'fuel'
  [../]

  # Temperature
  [./temp_time_derivative]
    type = MatINSTemperatureTimeDerivative
    variable = temp
  [../]

  [./temp_diffusion]
    type = MatDiffusion
    D_name = 'k'
    variable = temp
  [../]

  [./temp_advection_fuel]
    type = ConservativeTemperatureAdvection
    velocity = '0 ${flow_velocity} 0'
    variable = temp
    #block = 'fuel'
  [../]

  [./temp_source_fuel]
    type = TransientFissionHeatSource
    variable = temp
    nt_scale=${nt_scale}
    #block = 'fuel'
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
  [./left]
    type = DirichletBC
    variable = temp
    boundary = 'left'
    value = 700
  [../]
  [./right]
    type = DirichletBC
    variable = temp
    boundary = 'right'
    value = 700
  [../]
  [./bottom]
    type = DirichletBC
    variable = temp
    boundary = 'bottom'
    value = 700
  [../]
  [./temp_advection_outlet]
    type = TemperatureOutflowBC
    variable = temp
    boundary = 'top'
    velocity = '0 ${flow_velocity} 0'
  [../]
[]


[Materials]
  [./fuel]
    type = GenericMoltresMaterial
    property_tables_root = '../../property_file_dir/newt_msre_fuel_'
    interp_type = 'spline'
    #block = 'fuel'
    prop_names = 'k cp'
    prop_values = '1. 1.'
    #prop_values = '.0553 1967' # Robertson MSRE technical report @ 922 K
  [../]
  [./rho_fuel]
    type = DerivativeParsedMaterial
    f_name = rho
    function = '1.e-1'
    #function = '2.146e-3 * exp(-1.8 * 1.18e-4 * (temp - 922))'
    args = 'temp'
    derivative_order = 1
  #  block = 'fuel'
  [../]
[]


[Executioner]
  #type = Steady
  type = Transient
  solve_type = 'PJFNK'
  num_steps = 5
  dt = 1
[]


[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]