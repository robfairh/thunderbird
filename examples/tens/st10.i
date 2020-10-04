[GlobalParams]
  displacements = 'disp_x disp_y'
[]

[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 2.
  ymax = 2.
  nx = 20
  ny = 20
  elem_type = QUAD9
[]

[Modules/TensorMechanics/Master]
  [./block1]
    strain = FINITE
    add_variables = true
    generate_output = 'stress_xx stress_yy strain_xx strain_yy'
  [../]
[]

[Materials]
  [./elasticity_tensor]
    type = ComputeIsotropicElasticityTensor
    youngs_modulus = 10e9
    poissons_ratio = 0.14
  [../]
  [./stress]
    #assumes finite strains and rotations increments
    type = ComputeFiniteStrainElasticStress
  [../]
[]

[BCs]
  [./left]
    type = PresetBC
    variable = disp_x
    boundary = bottom
    value = 0.0
  [../]
  [./bottom]
    type = PresetBC
    variable = disp_y
    boundary = bottom
    value = 0.0
  [../]
  [./top]
    type = FunctionPresetBC
    variable = disp_y #change the variable to reflect the new displacement names
    boundary = top
    function = '0.0007*t'
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
  end_time = 5

  solve_type = 'PJFNK'

  petsc_options = '-snes_ksp_ew'
  petsc_options_iname = '-pc_type -sub_pc_type -pc_asm_overlap -ksp_gmres_restart'
  petsc_options_value = 'asm lu 1 101'
[]

[Postprocessors]
  [./ave_stress_bottom]
    type = SideAverageValue
    variable = stress_yy
    boundary = bottom
  [../]
  [./ave_strain_bottom]
    type = SideAverageValue
    variable = strain_yy
    boundary = bottom
  [../]
[]

[Outputs]
  exodus = true
  perf_graph = true
  csv = true
[]
