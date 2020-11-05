double double__x = 45.45 ;
double double__y = 30.20 ;

void setup() {
   Serial.begin(9600);
   Serial.print("cos num = ");
   Serial.println (cos (double__x) ); // returns cosine of x
   Serial.print("absolute value of num = ");
   Serial.println (fabs (double__x) ); // absolute value of a float
   Serial.print("floating point modulo = ");
   Serial.println (fmod (double__x, double__y)); // floating point modulo
   Serial.print("sine of num = ");
   Serial.println (sin (double__x) ) ;// returns sine of x
   Serial.print("square root of num : ");
   Serial.println ( sqrt (double__x) );// returns square root of x
   Serial.print("tangent of num : ");
   Serial.println ( tan (double__x) ); // returns tangent of x
   Serial.print("exponential value of num : ");
   Serial.println ( exp (double__x) ); // function returns the exponential value of x.
   Serial.print("cos num : ");

   Serial.println (atan (double__x) ); // arc tangent of x
   Serial.print("tangent of num : ");
   Serial.println (atan2 (double__y, double__x) );// arc tangent of y/x
   Serial.print("arc tangent of num : ");
   Serial.println (log (double__x) ) ; // natural logarithm of x
   Serial.print("cos num : ");
   Serial.println ( log10 (double__x)); // logarithm of x to base 10.
   Serial.print("logarithm of num to base 10 : ");
   Serial.println (pow (double__x, double__y) );// x to power of y
   Serial.print("power of num : ");
   Serial.println (square (double__x)); // square of x
}

void loop() {

}
