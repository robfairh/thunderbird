[Mesh]
  file = rectangle.msh
[]

[GlobalParams]
  num_groups = 2
  num_precursor_groups = 6
  group_fluxes = 'group1 group2'
  temperature = temp
  sss2_input = false
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

  # Neutronics: Group2
  [./time_group2]
    type = NtTimeDerivative
    variable = group2
    group_number = 2
  [../]
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
  [./temp_diffusion]
    type = MatDiffusion
    D_name = 'k'
    variable = temp
  [../]
[]

[BCs]
  [./vacuum_flux1L]
    type = DirichletBC
    variable = group1
    boundary = 'left right'
    value = 0
  [../]
  [./vacuum_flux2L]
    type = DirichletBC
    variable = group2
    boundary = 'left right'
    value = 0
  [../]
  [./left]
    type = DirichletBC
    variable = temp
    boundary = 'left right'
    value = 700
  [../]
[]

[Materials]
  [./fuel]
    type = GenericMoltresMaterial
    property_tables_root = '../../property_file_dir/newt_msre_fuel_'
    interp_type = 'spline'
    #block = 'fuel'
    prop_names = 'k'
    prop_values = '1.'
  [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Executioner]
  type = Transient
  end_time = 100

  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-6

  solve_type = 'NEWTON'
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type'
  petsc_options_value = 'lu       NONZERO'
  line_search = 'none'
  # petsc_options_iname = '-snes_type'
  # petsc_options_value = 'test'
  nl_max_its = 30
  l_max_its = 100
  dtmin = 1e-5
  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1e-3
    cutback_factor = 0.4
    growth_factor = 1.2
    optimal_iterations = 20
  [../]
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]