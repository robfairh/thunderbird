[Mesh]
  # We use a pre-generated mesh file (in exodus format).
  # This mesh file has 'top' and 'bottom' named boundaries defined inside it.
  file = rectangle.msh
[]

[Variables]
  [./temperature]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = temperature
  [../]

  [./conv]
    type = Convection
    variable = temperature
    velocity = '0.0 1.0 0.0'
  [../]
[]

[BCs]
  [./bottom] # arbitrary user-chosen name
    type = DirichletBC
    variable = temperature
    boundary = 'bottom' # This must match a named boundary in the mesh file
    value = 0
  [../]

  [./left]
    type = DirichletBC
    variable = temperature
    boundary = 'left'
    value = 1
  [../]

  [./right]
    type = DirichletBC
    variable = temperature
    boundary = 'right'
    value = 1
  [../]
[]

[Executioner]
  type = Steady
  solve_type = 'PJFNK'
  file_base = 'out'
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
