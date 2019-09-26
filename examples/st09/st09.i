[GlobalParams]
  gravity = '0 -9.81 0'
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

[MeshModifiers]
  [./bottom_left]
    type = AddExtraNodeset
    new_boundary = center
    coord = '1 1'
  [../]
[]

[Variables]
  [./stress_x]
    order = FIRST
    family = LAGRANGE
  [../]

  [./u]
    order = FIRST
    family = LAGRANGE
  [../]

  [./stress_y]
    order = FIRST
    family = LAGRANGE
  [../]

  [./v]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./strain_x]
    order = FIRST
    family = LAGRANGE
  [../]

  [./strain_y]
    order = FIRST
    family = LAGRANGE
  [../]

  [./tau_xy]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[Kernels]
  [./eq_x]
    type = Equilibrium
    variable = stress_x
    tau_xy = tau_xy
    component = 0
  [../]

  [./defor_x]
    type = Deformation
    variable = u
    strain_x = strain_x
    strain_y = strain_y
    component = 0
  [../]

  [./eq_y]
    type = Equilibrium
    variable = stress_y
    tau_xy = tau_xy
    component = 1
  [../]

  [./defor_y]
    type = Deformation
    variable = v
    strain_x = strain_x
    strain_y = strain_y
    component = 1
  [../]
[]

[AuxKernels]
  [./const_x]
    type = AuxConstitutive
    variable = strain_x
    sigma_x = stress_x
    sigma_y = stress_y
    E = 10e9
    nu = 0.14
    component = 0
  [../]

  [./const_y]
    type = AuxConstitutive
    variable = strain_y
    sigma_x = stress_x
    sigma_y = stress_y
    E = 10e9
    nu = 0.14
    component = 1
  [../]

  [./shear_s]
    type = AuxShear
    variable = tau_xy
    u_def = u
    v_def = v
    E = 10e9
    nu = 0.14
  [../]
[]

[BCs]
  #[./left1]
  #  type = DirichletBC
  #  variable = stress_x
  #  boundary = 'left'
  #  value = 0
  #[../]

  [./top1]
    type = DirichletBC
    variable = stress_y
    boundary = 'top'
    value = 0
  [../]

  [./left2]
    type = DirichletBC
    variable = u
    boundary = 'bottom'
    value = 0
  [../]

  [./top2]
    type = DirichletBC
    variable = v
    boundary = 'bottom'
    value = 0
  [../]
[]

[Materials]
  [./const]
    type = GenericConstantMaterial
    prop_names = 'rho nu'
    prop_values = '1700 0.14'
  [../]
[]

[Preconditioning]
  [./SMP_PJFNK]
    type = SMP
    full = true
    solve_type = JFNK
  [../]
[]

[Executioner]
  type = Steady
  petsc_options_iname = '-ksp_gmres_restart -pc_type -sub_pc_type -sub_pc_factor_levels'
  petsc_options_value = '300                bjacobi  ilu          4'
  line_search = none
  nl_rel_tol = 1e-10
  nl_max_its = 12
  l_tol = 1e-6
  l_max_its = 300
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
[]
