// n is an array of 10 integers
int n[ 10 ] = { 32, 27, 64, 18, 95, 14, 90, 70, 60, 37 } ;

void setup () {
  Serial.begin(9600);
}

void loop () {
   for ( int i = 0; i < 10; ++i ) {
      Serial.print (i) ;
      Serial.print ('\r') ;
   }
   for ( int j = 0; j < 10; ++j ) // output each array element's value 
   {
      Serial.print (n[j]) ;
      Serial.print ("\r") ;
   } 
}
