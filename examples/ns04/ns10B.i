# This input file tests Dirichlet pressure in/outflow boundary conditions for the incompressible NS equations.
[GlobalParams]
  gravity = '0 0 0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 1.0
  ymin = 0
  ymax = 2.
  nx = 10
  ny = 30
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
  [./temp_time]
    type = MatINSTemperatureTimeDerivative
    variable = temp
  [../]
  [./temp_advection]
    type = INSTemperature
    variable = temp
    u = vel_x
    v = vel_y
  [../]
[]

[BCs]
  [./x_no_slip]
    type = DirichletBC
    variable = vel_x
    boundary = 'left top bottom'
    value = 0.0
  [../]
  [./y_no_slip]
    type = DirichletBC
    variable = vel_y
    boundary = 'left right'
    value = 0.0
  [../]
  [./inlet_p]
    type = DirichletBC
    variable = p
    boundary = bottom
    value = 0.
  [../]
  [./outlet_p]
    type = DirichletBC
    variable = p
    boundary = top
    value = 100.0
  [../]
  [./q_wall_left]
    type = DirichletBC
    variable = temp
    boundary = 'left right'
    value = 100.0
  [../]
  [./T_wall]
    type = DirichletBC
    variable = temp
    boundary = top
    value = 0.0
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    block = 0
    prop_names = 'rho mu k cp'
    prop_values = '10  1 1 1'
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
