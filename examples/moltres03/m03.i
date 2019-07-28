[Mesh]
  file = rectangle.msh
[]

flow_velocity = 1.0

[GlobalParams]
  temperature = temp
[]


[Variables]
  [./temp]
    order = FIRST
    family = LAGRANGE
  [../]
[]


[Kernels]
  [./temp_diffusion]
    type = MatDiffusion
    D_name = 'k'
    variable = temp
  [../]

  [./temp_advection_fuel]
    type = ConservativeTemperatureAdvection
    variable = temp
    velocity = '0.0 ${flow_velocity} 0.0'
  [../]

  [./temp_source]
    type = TempSource
    variable = temp
  [../]
[]


[BCs]
  [./bot]
    type = DirichletBC
    variable = temp
    boundary = 'bottom'
    value = 0
  [../]
  [./temp_advection_outlet]
    type = TemperatureOutflowBC
    variable = temp
    boundary = 'top'
    velocity = '0.0 ${flow_velocity} 0.0'
  [../]

  [./left]
    type = DirichletBC
    variable = temp
    boundary = 'left'
    value = 0
  [../]
  [./right]
    type = DirichletBC
    variable = temp
    boundary = 'right'
    value = 0
  [../]
[]


[Materials]
  [./fuel]
    type = GenericConstantMaterial
    prop_names = 'k cp'
    prop_values = '1. 1.' # Robertson MSRE technical report @ 922 K
  [../]

  [./rho_fuel]
    type = DerivativeParsedMaterial
    f_name = rho
    function = '1.0'
    #function = '2.146e-3 * exp(-1.8 * 1.18e-4 * (temp - 922))'
    args = 'temp'
    derivative_order = 1
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