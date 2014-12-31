
// demo con tarjeta sd + red + temperatura
#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>
#include <DHT.h>

// Configuracion del Ethernet Shield
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xEE}; // Direccion MAC
byte ip[] = { 192,168,3,050 }; // Direccion IP del Arduino
byte server[] = { 192,168,2,10 }; // Direccion IP del servidor
EthernetClient client; 

const int chipSelect = 4;  
#define DHTPIN 2   
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup(void) {
  Serial.begin(9600);
  dht.begin();
 pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)){
    Serial.println("Error al leer la tarjeta.");
    return;
  }
  Ethernet.begin(mac, ip); // Inicializamos el Ethernet Shield
  delay(1000); // Esperamos 1 segundo
}

void loop(void) {
  float t = dht.readTemperature();

  File dataFile = SD.open("valor.txt", FILE_WRITE);
  // Si el fichero es correcto escribimos en el.
  if (dataFile) {
    // Escribimos en el fichero la temperatura"
    dataFile.print("*C: ");
    // A continuacion escribimos el valor de la variable pot y saltamos a la linea siguiente.
    dataFile.println(t);
    // Cerramos el archivo.
    dataFile.close();
   
   // Avisamos de que se ha podido escribir correctamente.
   Serial.println("impresion correcta");
   Serial.print("*C: ");
   Serial.println(t);
  // Si no pudimos escribir en el fichero avisamos por el puerto serie.
  }else{
    Serial.println("Error al escribir en valor.txt");
  }
 
  // Esperamos 5s para tomar la siguiente medida.
  delay(5000);

}
