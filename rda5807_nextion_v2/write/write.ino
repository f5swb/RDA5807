// Exemple pour écrire la valeur 125 à l’adresse 14 de l’EEPROM de son Arduino
// avec la fonction EEPROM.write
#include <EEPROM.h>
int adresse = 14;
int valeur = 10250;

void setup() {
  //EEPROM.put(adresse, valeur);
 Serial.begin(9600) ;
  valeur = EEPROM.get(adresse, valeur);  // Retourne la valeur contenue dans l'eeprom, à l’adresse "14"

  Serial.print("La fréquence mémorisée en kHz est = "); Serial.println(valeur); 
  
  
}

void loop() {
}
