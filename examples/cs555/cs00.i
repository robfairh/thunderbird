[GlobalParams]
  gravity = '0 -9.8 0'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmin = 0
  xmax = 1.0
  ymin = 0
  ymax = 1.0
  nx = 20
  ny = 20
  elem_type = QUAD9
[]

[Variables]
  [./temp]
    order = SECOND
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./tempTimeDeriv]
    type = MatINSTemperatureTimeDerivative
    variable = temp
  [../]
  [./tempAdvectionDiffusion]
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
    boundary = 'top bottom left right'
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
    value = 1.0
  [../]
  [./outlet_p]
    type = DirichletBC
    variable = p
    boundary = top
    value = 0.0
  [../]

  [./tempbc]
    type = DirichletBC
    variable = temp
    boundary = 'left right'
    value = 10
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    block = 0
    prop_names = 'rho mu    k     cp  alpha'
    prop_values = '1  1e-1  1e-3  1   1e-2'
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
  end_time = 100

  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-6

  solve_type = 'NEWTON'
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'
  petsc_options_iname = '-pc_type -pc_factor_shift_type'
  petsc_options_value = 'lu       NONZERO'
  line_search = 'none'
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
  #execute_on = 'timestep_end'
  exodus = true
[]
