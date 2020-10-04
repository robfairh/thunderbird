[Mesh]
  type = GeneratedMesh
  dim = 2
  xmax = 2.
  ymax = 2.
  nx = 20
  ny = 20
  elem_type = QUAD9
  boundary_id = '1 2 3 4' #Assign names to boundaries to make things clearer
  boundary_name = 'top left right bottom'
[]

[GlobalParams]
  disp_x = disp_x
  disp_y = disp_y
[]

[Variables]
  [./disp_x]
    order = FIRST
    family = LAGRANGE
  [../]
  [./disp_y]
    order = FIRST
    family = LAGRANGE
  [../]
[]

#[SolidMechanics]
#  [./solid]
#  [../]
#[]

[Kernels]
  [./gravity_y]
    #Gravity is applied to bridge
    type = Gravity
    variable = disp_y
    value = -9.81
  [../]
[]

[AuxVariables]
  [./von_mises]
    #Dependent variable used to visualize the Von Mises stress
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[AuxKernels]
  [./von_mises_kernel]
    #Calculates the von mises stress and assigns it to von_mises
    type = MaterialTensorAux
    variable = von_mises
    tensor = stress
    execute_on = timestep_end
    quantity = VonMises
  [../]
[]

[BCs]
  [./Pressure]
    [./load]
      #Applies the pressure
      boundary = top
      factor = 5e5 # Pa
    [../]
  [../]
  [./anchor_x]
    #Anchors the bottom and sides against deformation in the x-direction
    type = PresetBC
    variable = disp_x
    boundary = 'left right bottom'
    value = 0.0
  [../]
  [./anchor_y]
    #Anchors the bottom and sides against deformation in the y-direction
    type = PresetBC
    variable = disp_y
    boundary = 'left right bottom'
    value = 0.0
  [../]
[]

[Materials]
  [./steel_elastic]
    type = Elastic
    block = 1
    youngs_modulus = 210e9 #Pa
    poissons_ratio = 0.3
    formulation = Linear
  [../]

  [./density_steel]
    #Defines the density of steel
    type = GenericConstantMaterial
    block = 1
    prop_names = density
    prop_values = 7850 # kg/m^3
  [../]
[]

[Preconditioning]
  [./SMP]
    #Creates the entire Jacobian, for the Newton solve
    type = SMP
    full = true
  [../]
[]

[Executioner]
  #We solve a steady state problem using Newton's iteration
  type = Steady
  solve_type = NEWTON
  nl_rel_tol = 1e-9
  l_max_its = 30
  l_tol = 1e-4
  nl_max_its = 10
  petsc_options_iname = '-pc_type -pc_hypre_type -ksp_gmres_restart'
  petsc_options_value = 'hypre boomeramg 31'
[]

[Outputs]
  [./exodus]
    #Outputs the result to an exodus file and converts the element stress output to a nodal output
    type = Exodus
    elemental_as_nodal = true
  [../]
[]