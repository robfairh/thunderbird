# To run: $MOOSE/moose_test-opt -i input1.i

# [GlobalParams]
#   gravity = '0 -9.81 0'
# []

[Mesh]
  file = 'geom01.msh'
[../]

[Variables]
  [./temp]
    order = FIRST
    family = LAGRANGE
    initial_condition = 100
  [../]
[]

[Kernels]
  [./Conduction]
    type = Diffusion
    variable = temp
    # diffusion_coefficient = 1.0
    # thermal_conductivity
  [../]

  [./Source]
    type = BodyForce
    variable = temp
    # value = 1.0
  [../]
[]

[BCs]
  [./inlet]
    boundary = 'base top'
    type = DirichletBC
    variable = temp
    value = 0
  [../]
[]

[Materials]
  [./fuel]
    type = GenericConstantMaterial
    prop_names = 'thermal_conductivity'
    prop_values = '1.0'  # [W/m/K]
  [../]
[]

[Executioner]
  type = Steady
  nl_rel_tol = 1e-6
  nl_abs_tol = 1e-5
  solve_type = 'NEWTON'
  petsc_options = '-snes_converged_reason -ksp_converged_reason -snes_linesearch_monitor'

  petsc_options_iname = '-pc_type -sub_ksp_type -snes_linesearch_minlambda'
  petsc_options_value = 'lu       preonly       1e-3'

  nl_max_its = 30
  l_max_its = 100
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Outputs]
  file_base = 'input01'
  exodus = true
[]