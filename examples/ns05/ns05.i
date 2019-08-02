# This input file tests Dirichlet pressure in/outflow boundary conditions for the incompressible NS equations.
[GlobalParams]
  gravity = '0 -9.81 0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 2.0
  ymin = 0
  ymax = 2.0
  nx = 20
  ny = 20
  elem_type = QUAD9
[]

[Variables]
  [./vel_x]
    order = SECOND
    family = LAGRANGE
  [../]
  [./vel_y]
    order = SECOND
    family = LAGRANGE
  [../]
  [./p]
    order = FIRST
    family = LAGRANGE
  [../]
  [./temp]
    order = SECOND
    family = LAGRANGE
  [../]
  [./deltaT]
    family = LAGRANGE
    order = SECOND
  [../]
[]

[Kernels]
  [./mass]
    type = INSMass
    variable = p
    u = vel_x
    v = vel_y
    p = p
  [../]
  [./x_time_deriv]
    type = INSMomentumTimeDerivative
    variable = vel_x
  [../]
  [./y_time_deriv]
    type = INSMomentumTimeDerivative
    variable = vel_y
  [../]
  [./x_momentum_space]
    type = INSMomentumLaplaceForm
    variable = vel_x
    u = vel_x
    v = vel_y
    p = p
    component = 0
    integrate_p_by_parts = false
  [../]
  [./y_momentum_space]
    type = INSMomentumLaplaceForm
    variable = vel_y
    u = vel_x
    v = vel_y
    p = p
    component = 1
    integrate_p_by_parts = false
  [../]
  [./buoyancy_x]
    type = INSBoussinesqBodyForce
    variable = vel_x
    dT = deltaT
    component = 0
    temperature = temp
  [../]
  [./buoyancy_y]
    type = INSBoussinesqBodyForce
    variable = vel_x
    dT = deltaT
    component = 1
    temperature = temp
  [../]
  [./temp_time]
    type = MatINSTemperatureTimeDerivative
    variable = temp
  [../]
  #[./temp_diffusion]
  #  type = MatDiffusion
  #  D_name = 'k'
  #  variable = temp
  #[../]
  [./temp_advection]
    type = INSTemperature
    variable = temp
    u = vel_x
    v = vel_y
  [../]
  [./deltaTCalc]
    type =  ConstantDifferenceAux
    variable = deltaT
    compareVar = temp
    constant = 900.0
  [../]
[]

[BCs]
  [./x_no_slip]
    type = DirichletBC
    variable = vel_x
    boundary = 'left right top bottom'
    value = 0.0
  [../]
  [./y_no_slip]
    type = DirichletBC
    variable = vel_y
    boundary = 'left right top bottom'
    value = 0.0
  [../]
  [./inlet_p]
    type = DirichletBC
    variable = p
    boundary = 'left right top bottom'
    value = 0.0
  [../]
  [./outlet_p]
    type = DirichletBC
    variable = p
    boundary = top
    value = 0.0
  [../]
  [./T_top]
    type = DirichletBC
    variable = temp
    boundary = top
    value = 800.0
  [../]
  [./T_bottom]
    type = DirichletBC
    variable = temp
    boundary = bottom
    value = 900.0
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    block = 0
    prop_names = 'rho mu k cp alpha'
    prop_values = '1e-1 1e-5 1e-2 1e3 1e-3'
  [../]
[]

[Preconditioning]
  [./SMP_PJFNK]
    type = SMP
    full = true
    solve_type = PJFNK
  [../]
[]

[Executioner]
  type = Transient
  petsc_options_iname = '-ksp_gmres_restart -pc_type -sub_pc_type -sub_pc_factor_levels'
  petsc_options_value = '300                bjacobi  ilu          4'
  line_search = none
  nl_rel_tol = 1e-12
  nl_max_its = 6
  l_tol = 1e-6
  l_max_its = 300
  num_steps = 5
  dt = 1
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
