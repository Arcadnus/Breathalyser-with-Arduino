#include <ESP8266WiFi.h>
#include <WiFiClient.h>
const char* ssid     = "AP CASA NOBRE";
const char* password = "DangoDaikazoku";

const char* host = "192.168.15.13";

int valor_ino1;
int valor_ino2;




void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Conectando com ");
  Serial.println(ssid);

 WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  Serial.print("conectado com ");
  Serial.println(host);

  WiFiClient client;
  
  const int httpPort = 80;
  
  if (!client.connect(host, httpPort)) {
    Serial.println("Falha na conexão");
    return;
  }

  valor_ino1 ++;
  valor_ino2 ++;
  
  
  String url = "/nodemcu/salvar.php?";
          url += "sensor1=";
          url += valor_ino1;
          url += "&sensor2=";
          url += valor_ino2;

  Serial.print("Requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
               
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
    if (line.indexOf("sucesso") != -1){
      Serial.println();
      Serial.println("AEW DEU BOA!");
    } else if (line.indexOf("erro_ao_salvar") != -1){
      Serial.println();
      Serial.println("IIHH FIOTE....");
    }
  }

  Serial.println();
  Serial.println("closing connection");

  delay(10000);
  
}
