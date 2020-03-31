/* 
 * Name: Ventilator_Preformance.ino
 * Authors: Luca Scotzniovsky, Clemente Guasch, Imran Matin
 * Description: TODO
 * Notes:
 * - Can declare global variables outside of function to persist during whole program, irrelevant of function calls.
 * - Can declare static variables inside function to persist during that function and its scope.
 */

// include mathematical functions
#include <math.h>
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7,8,9,10,11,12);

// Piston Outer Diameter in cm
const double OD = 10.16;
// Piston Inner Diameter in cm
const double ID = 9.398; 
// Cross-sectional Area of Piston in m^2
const double AP = M_PI * pow(((OD + ID)/4), 2) * pow(10,-4);
// Tube Diameter in m
const double TD = 0.0635;
// Cross-sectional Area of Tube in m^2 
const double AT = M_PI * pow((TD/2), 2);
// TODO: Definition? Air density in kg/m^3
const double RHO_AIR = 1.225;

// Conversion Factor from Pa to cmH20
const double CONV_PA_CMH20 = 0.010197162129779;
// Conversion factor from N to lbf 
const double CONV_N_TO_LBF = .2248089;
// Absolute roughness of tubing in m
const double E = .0000015;
// TODO: (solenoid head loss value; will use later, ignore for now)
const double Ksol = 0;

/* 
 * Inputs/Dials
 * Potentiometer already sets them to zero.
 */
// Initializing oxygen fraction (lowest is at 21% for pure air) (Fraction of inspired oxygen)
double FiO2 = .21;
// Initializing breaths per minute (respiratory rate)
double BPM = 0;
// Initializing inspiratory pressure
double Pinsp = 0;
// Initializing expiratory pressure
double Pexp = 0;
// Initializing insp-exp ratio (E/I)
double IE = 0;


// Based off FI02 percentage
// Initializing density of gas going to patient 
double rho = 0;


// based off of BPM and IE
// Initializing inspiratory time
double Tinsp = 0;
// Initializing expiratory time 
double Texp = 0; 


/*
 * initalized/changes and not controlled by UI
 * 
 */
// Tidal Volume
double Vtidal = 0;


/* 
 * List of variables/values still needed
 */
// applied motor rotation speed of gear
// flow rate


/*
 * << SET PIN MODES BELOW IN VOID SETUP LOOP >>
 */
// Pin for FiO2 adjustment
int FI02_PIN = A1;


/*
 * Function Name: setup
 * Description: Setup code to run once for initalizing ventilator control values upon power up.
 */
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();

  // Set potentiometer knobs mode to INPUT 
  pinMode(FI02_PIN, INPUT);
}

/*
 * Function Name: loop
 * Description: Code that will run repeateadly once setup is completed.
 */
void loop() {
  // Sets the cursor to col 0 and row 0
  lcd.setCursor(0,0);
  // Prints value on FI02_PIN to LCD
  lcd.print("FI02_PIN: ");
  lcd.print(analogRead(FI02_PIN));




  // 1. Function for reading of FiO2 in a decimal; reading must be between .21 and 1
  // Syntax: analogWrite(int pin, int value)
  // double FiO2 = analogWrite(PIN, FiO2) * (1- .21)/1023 + .21

  // 2. density of air going to patient using FiO2
  // 
  double rho = (RHO_O2 - RHO_AIR) * FiO2 / .79  + (RHO_AIR - (.21 * RHO_O2)) / .79;

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