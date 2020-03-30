/* 
 * Name: Ventilator_Preformance.ino
 * Authors: Luca Scotzniovsky, Clemente Guasch, Imran Matin
 * Description: TODO
 */

// include mathematical functions
#include <math.h>

/*
 * Function Name: setup
 * Description: Setup code to run once for initalizing ventilator control values upon power up.
 */
void setup() {
  // TODO: Variables need to be adjusted to electrical signals

  // calculate arc tangent of x (type double)
  double pi = atan(1.00);

  // Piston Outer Diameter in cm converted from inch (not sure about data type)
  double OD = convertInToCm(4); 

  // Piston Inner Diameter in cm (not sure about data type)
  double ID = convertInToCm(3.7); 

  // Cross-sectional Area of Piston in m^2
  double AP = crossSecAreaOfPiston(pi, OD, ID);

  // Tube Diameter in m converted from inch to cm to m
  double TD = convertInToCm(.25)/100;

  // Cross-sectional Area of Tube in m^2 
  double AT = pi * sq(TD/2);

  // Air density in kg/m^3
  double rho_air = 1.225;
  // Air density in kg/m^3
  double rho_O2 = 1.331;

  // Conversion Factor from Pa to cmH20
  double Pa_cmH20 = 0.010197162129779;
  // Conversion factor from N to lbf 
  double N_lb = .2248089; 

  // Absolute roughness of tubing in m
  double E = .0015 / 1000;

  // (solenoid head loss value; will use later, ignore for now)
  double Ksol = 0;

  /*
   * Unknowns
   */
  // Tidal Volume
  double Vtidal = 0;


  /* 
   * Inputs/Dials
   */
  // Initializing inspiratory pressure
  double Pinsp = 0;
  // Initializing expiratory pressure
  double Pexp = 0;
  // Initializing oxygen fraction (lowest is at 21% for pure air)
  double FiO2 = .21;
  // Initializing breaths per minute
  double BPM = 0;
  // Initializing insp-exp ratio (E/I)
  double IE = 0;
  // Initializing density of gas going to patient 
  double rho = 0; 
  // Initializing inspiratory time
  double Tinsp = 0;
  // Initializing expiratory time 
  double Texp = 0; 

  /* 
   * List of variables/values still needed
   */
  // applied motor rotation speed of gear
  // flow rate


  /*
   * << SET PIN MODES BELOW IN VOID SETUP LOOP >>
   */
  // Pin for FiO2 adjustment
  int Pin_FiO2 = 0;
}

/*
 * Function Name: loop
 * Description: Code that will run repeateadly once setup is completed.
 */
void loop() {
  /* 
  * Must change variables in setup() to be local vars in loop() or global vars
  */

  // 1. Function for reading of FiO2 in a decimal; reading must be between .21 and 1
  // Syntax: analogWrite(int pin, int value)
  // double FiO2 = analogWrite(PIN, FiO2) * (1- .21)/1023 + .21

  // 2. density of air going to patient using FiO2
  // 
  double rho = (rho_O2 - rho_air) * FiO2 / .79  + (rho_air - (.21 * rho_O2)) / .79;

  // 3. 
  // insp. pressure, exp. pressure, BPM, insp-exp ratio inputs from knobs similar to FiO2 reading above

  // BPM between 6 and 40
  // Inspiratory time; need to determine actual BPM and IE using potentiometer relations
  double Tinsp = 60 / (BPM * (1+IE));
  // Determining expiratory time given BPM and Tinsp
  double Texp = Tinsp * IE;

  // 4. 
  // Need to find way to determine tidal volume
}


/*
 * Name: convertInToCm
 * Description: Convert inches into centimeters. 
 */
double convertInToCm(double inches) {
  return inches * 2.54;
}

/*
 * Name: sq
 * Description: Square the input value by itself
 */
double sq(double x) {
  return x * x;
}

/*
 * Name: crossSecAreaOfPiston
 * Description: Calculate cross-sectional area of a piston.
 */
double crossSecAreaOfPiston(double pi, double OD, double ID) {
  return pi * sq((OD + ID)/4) * pow(10,-4);
}