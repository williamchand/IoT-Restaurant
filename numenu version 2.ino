#include <ESP8266WiFi.h>
#include <String.h>
#include <WString.h>
#include <LiquidCrystal.h>
#include <ESP8266WebServer.h>

LiquidCrystal lcd(0,4,14,12,13,15);
// Replace with your network credentials
const char* ssid = "NuMenuSSID";
const char* password = "password";
const int buttonPin = 2;
int buttonState = 0;
int i = 0;
String makanan,minuman,cashback;
WiFiServer server(80);
//untuk parsing
String teststring = String(100);
String ReadString;
int ind1 = 0;
int ind2 = 0;
 int kondisi = 0;
//sampai sini parsing
void setup()
{

  lcd.begin(16,2);
  pinMode(5, INPUT);
  
    delay(1000);
    Serial.begin(9600);
    Serial.println();

    WiFi.softAP(ssid, password);

    IPAddress apip = WiFi.softAPIP();
    Serial.print("visit: \n");
    Serial.println(apip);
    server.begin();
    Serial.println("HTTP server beginned");
}


// prepare a web page to be send to a client (web browser)

void loop()
{
    lcdtampilan1();
    Wificontrol();
}

void Wificontrol()
{
  WiFiClient client = server.available(); 
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");
    while(client.connected()){
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        char c = client.read();
        //read char by char HTTP request
        if (ReadString.length() < 100) {

          //store characters to string 
          ReadString += c; 
          //Serial.print(c);
        } 

        //if HTTP request has ended
        // wait for end of client's request, that is marked with an empty line
        if (c == '\n') {
          Serial.println(ReadString);
          client.print(prepareHtmlPage());
          client.flush();
          client.print(Preparehtml2page());
          client.flush();
          client.print(Preparehtml3page());
          client.flush();
          delay(500); // give the web browser time to receive the data
           // close the connection:
            client.stop();
         Serial.println("[Client disonnected]");
         if(ReadString.indexOf('?') >0)//checks for ?
          {
            ind1=ReadString.indexOf('?');
            ind2 = ReadString.lastIndexOf(' ');
            teststring = ReadString.substring(ind1+1, ind2);
            Serial.println(teststring); 
            ind1 = teststring.indexOf('=');
            ind2 = teststring.indexOf('&');
            makanan = teststring.substring(ind1+1, ind2);
            makanan.replace('+', ' ');
            teststring = teststring.substring(ind2+1,teststring.length());
            ind1 = teststring.indexOf('=');
            ind2 = teststring.indexOf('&');
            minuman = teststring.substring(ind1+1, ind2);
            minuman.replace('+', ' ');
            teststring=teststring.substring(ind2+1,teststring.length());
            ind1 = teststring.indexOf('=');
            cashback = teststring.substring(ind1+1, teststring.length());
            kondisi = 1;
            lcdtampilan2();
            Serial.println(makanan);
            Serial.println(minuman);
            Serial.println(cashback);
            //clearing string for next read
            ReadString="";
          }
        }
      }
    }
  }
}

String prepareHtmlPage()
{
  String htmlPage = 
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "\r\n" +
            "<!DOCTYPE html>\r\n"+
"<html>\r\n"+
"<style>\r\n"+
".button {\r\n"+
"   background-color: #990033;\r\n"+
"   border: none;\r\n"+
"   color: white;\r\n"+
"   padding: 2px 10px;\r\n"+
"   text-align: center;\r\n"+
"   cursor: pointer;\r\n"+
"   border-radius:25px;\r\n"+
"}"+
".bigbutton1 {\r\n"+
"   position: absolute;\r\n"+
"   width: 210px;\r\n"+
"   height: 100px;\r\n"+
"   background-color: #33FF33;\r\n"+
"   font-weight: normal;\r\n"+
"   color: blue;\r\n"+
"   text-align: center;\r\n"+
"  size: 30px\r\n"+
"  cursor:pointer;\r\n"+
"   font-size: 45px;\r\n"+
"   margin-top: 0px;\r\n"+
"   border-radius:25px;\r\n"+
"}\r\n"+
".bigbutton2 {\r\n"+
"   position: absolute;\r\n"+
"   width: 210px;\r\n"+
"   height: 100px;\r\n"+
"   background-color: #33FF33;\r\n"+
"   font-weight: normal;\r\n"+
"   color: blue;\r\n"+
"   text-align: center;\r\n"+
"   size: 30px\r\n"+
"   cursor:pointer;\r\n"+
"   font-size: 45px;\r\n"+
"   margin-top: 100px;\r\n"+
"   border-radius:25px;\r\n"+
"}\r\n"+
".textbox{\r\n"+
"   background-color: #AAAAFF;\r\n"+
"   border: 6px solid #0000FF;\r\n"+
"   color: red;\r\n"+
"   padding: 2px 10px;\r\n"+
"   text-align: center;\r\n"+
"   cursor: pointer;\r\n"+
"   border-radius:15px;\r\n"+
"}\r\n"+
"#centerDoc {\r\n"+
"   position: absolute;\r\n"+
"   padding: 0 0 0 10px; /*top right bottom left*/\r\n"+
"   margin-top: 50px;\r\n"+
"   width: 650px;\r\n"+
"   height: 600px;\r\n"+
"   margin-left: 235px;\r\n"+
"   background-color: #ffdddd;\r\n"+
"   border-left: 6px solid #f44336;\r\n"+
"   color: #FF11BB;\r\n"+
"   border-radius:25px;\r\n"+
"}\r\n"+
"#ItemDoc {\r\n"+
"   position: absolute;\r\n"+
"}\r\n"+
"#navigation {\r\n"+
"   border-radius:10px;\r\n"+
"   background: yellow;\r\n"+
"   position: absolute;\r\n"+
"   width: 210px;\r\n"+
"   height: 600px;\r\n"+
"   margin: 0;\r\n"+
"   margin-top: 0px;\r\n"+
"   border-right: 1px solid #FFCC11;\r\n"+
"   font-weight: normal;\r\n"+
"   font-size: 18px;\r\n"+
"   border-left: 6px solid #FFCC11;\r\n"+
"   color: #FF1111;\r\n"+
"}\r\n"+
"#NumberDoc {\r\n"+
"   position: absolute;\r\n"+
"   padding: 0 0 10 0; \r\n"+
"   margin-top: 0;\r\n"+
"   margin-left: 400px;\r\n"+
"   width: 400px;\r\n"+
"}\r\n"+
"#PriceDoc {\r\n"+
"   position: absolute;\r\n"+
"   padding: 0 0 10 0; /*top right bottom left*/\r\n"+
"   margin-top: 0;\r\n"+
"   margin-left: 200px;\r\n"+
"   width: 400px;\r\n"+
"}\r\n"+
"#RightDoc {\r\n"+
"   position: absolute;\r\n"+
"   padding: 0 0 10px 0; /*top right bottom left*/\r\n"+
"   margin-top: 0px;\r\n"+
"   margin-left: 600px;\r\n"+
"}\r\n"+
"#titles {\r\n"+
"font-size: 40px;\r\n"+
"}\r\n"+
"</style>\r\n"+
"<script>\r\n"+
"var food =['NasiPutih','NasiGoreng','CumiGoreng','AyamGoreng','SteakAyam','Kepiting'];\r\n"+
"var pricefood = [4000,12000, 10000, 10000, 11000,18000];\r\n"+
"var foodnumber = [];\r\n"+
"var drink = ['OrangeJuice','PapayaJuice','AirPutih','TehKotak','Espresso'];\r\n"+
"var pricedrink = [8000,9000,3000,4000,30000];\r\n"+
"var drinknumber = [];\r\n"+
"var itemlist;\r\n"+
"var i = 0;\r\n"+
"var price = 0;\r\n"+
"var cashback = 0;\r\n"+
"while (i <food.length) {foodnumber[i] = 0;i++;}\r\n"+
"i = 0;\r\n"+
"while (i <drink.length) {drinknumber[i] = 0;i++;}\r\n"+
"function processbeli() {\r\n"+
"var phraseElement = document.getElementById('phrase');\r\n";
  return htmlPage;
}
String Preparehtml2page(){
  String htmlpage=String("var response ='';\r\n")+
"i = 0;\r\n"+
"price = 0;\r\n"+
"response += '<div id=RightDoc><a class=button onclick=processcekmoney()';\r\n"+
"response += '>PAY</a></div><div id=titles>PEMBAYARAN</div>';\r\n"+
"while (food[i]) {if (foodnumber[i]>0){price +=foodnumber[i]*pricefood[i];}i++;}\r\n"+
"i=0;\r\n"+
"while (drink[i]){if (drinknumber[i]>0){price +=drinknumber[i]*pricedrink[i];}i++;}\r\n"+
"response += 'Harga yang perlu dibayarkan = '+price +'<br>';\r\n"+
"response += '<input type=number value=0 id=bayar class=textbox><br><br>';\r\n"+
"response +='<div id=titles>List Makanan</div>';\r\n"+
"i=0;\r\n"+
"while (food[i]){\r\n"+
"if (foodnumber[i]>0){\r\n"+
"response += '<p><div id=ItemDoc>'+food[i]+'</div><div id=PriceDoc>';\r\n"+
"response += foodnumber[i]+' Porsi</div></p><br>';\r\n"+
"}i++;}\r\n"+
"i=0;\r\n"+
"while (drink[i]){\r\n"+
"if (drinknumber[i]>0){\r\n"+
"response += '<p><div id=ItemDoc>'+drink[i]+'</div><div id=PriceDoc>';\r\n"+
"response += drinknumber[i]+' Gelas</div></p><br>'  ;\r\n"+
"}i++;}\r\n"+
"phraseElement.innerHTML = response;}\r\n"+
"function processcekmoney() {\r\n"+
"var money = document.getElementById('bayar').value;\r\n"+
"cashback = money - price;\r\n"+
"var response = '';\r\n"+
"i = 0;\r\n"+
"response +='?Makanan=';\r\n"+
"while (food[i]){\r\n"+
"if (foodnumber[i]>0){\r\n"+
"response += food[i]+'+'+foodnumber[i]+'+buah/n';}i++;}\r\n"+
"i=0;\r\n"+
"response+='&Minuman=';\r\n"+
"while (drink[i]){\r\n"+
"if (drinknumber[i]>0){\r\n"+
"response += drink[i]+'+'+drinknumber[i]+'+gelas/n';}i++;}\r\n"+
"response += '&CASH='+cashback;\r\n"+
"location.href=response;\r\n"+
"if (price>0){\r\n"+
"if (cashback >= 0) {\r\n"+
"processakhir();\r\n"+
"}\r\n"+
"else {\r\n"+
"alert('Uang Anda Tidak Cukup transaksi gagal');\r\n"+
"}\r\n"+
"}\r\n"+
"else{\r\n"+
"alert('Anda Belum Memesan transaksi gagal');\r\n"+
"}\r\n"+
"}\r\n"+
"function processakhir() {\r\n"+
"var response = 'Silahkan Tunggu makanannya ^_^ kembaliannya RP. '+cashback;\r\n"+
"alert(response);\r\n"+
"}\r\n"+
"function addf(j){\r\n"+
"foodnumber[j]++;\r\n"+
"foodlist();\r\n"+
"}\r\n"+
"function minf(j){\r\n"+
"if (foodnumber[j]>0){\r\n"+
"foodnumber[j]--;\r\n"+
"}\r\n"+
"foodlist();\r\n"+
"}\r\n"+
"function addd(j){\r\n"+
"drinknumber[j]++;\r\n"+
"drinklist();\r\n"+
"}\r\n"+
"function mind(j){\r\n"+
"if (drinknumber[j]>0){\r\n"+
"drinknumber[j]--;\r\n"+
"}\r\n"+
"drinklist();\r\n"+
"}\r\n";
            return htmlpage;
  }
String Preparehtml3page(){
  String htmlpage=String("function foodlist(){\r\n")+
"var phraseElement = document.getElementById('phrase');\r\n"+
"var response = '<div id=RightDoc>';\r\n"+
"response += '<input type=button class=button value=Buy onclick=processbeli() Button>';\r\n"+
"response += '</div><div id=titles>FOOD</div>';\r\n"+
"i = 0;\r\n"+
"while (food[i]) {\r\n"+
"response += '<p><div id=ItemDoc>'+food[i]+'</div><div id=PriceDoc>'+ pricefood[i];\r\n"+
"response += '</div><div id=NumberDoc>';\r\n"+
"response += '<input type=button class=button value=+ onclick=addf('+i+') Button> ';\r\n"+
"response += foodnumber[i];\r\n"+
"response += '<input type=button class=button value=- onclick=minf('+i+') Button></div></p><br>';\r\n"+
"i++;\r\n"+
"}\r\n"+
"phraseElement.innerHTML = response;\r\n"+
"}\r\n"+
"function drinklist(){\r\n"+
"var phraseElement = document.getElementById('phrase');\r\n"+
"var response ='<div id=RightDoc><input type=button class=button value=Buy onclick=processbeli() Button>';\r\n"
"response += '</input></div><div id=titles>DRINK</div>';\r\n"+
"i = 0;\r\n"+
"while (drink[i]) {\r\n"+
"response += '<p><div id=ItemDoc>'+drink[i]+'</div><div id=PriceDoc>'+ pricedrink[i]+'</div>';\r\n"+
"response += '<div id=NumberDoc>';\r\n"
"response += '<input type=button class=button value=+ onclick=addd('+i+') Button>';\r\n"+
"response += drinknumber[i];\r\n"
"response += '<input type=button class=button value=- onclick=mind('+i+') Button></div></p><br>'; \r\n"+
"i++;}\r\n"+
"phraseElement.innerHTML = response;}\r\n"+
"window.onload = foodlist;\r\n"+
"</script>\r\n"+
"<head> </head>\r\n"+
"<body bgcolor=#AA33AA onload='GetArduinoIO()'>\r\n"+
"<div id=navigation>\r\n"+
"NUMENU RESTAURANT<br>\r\n"+
"<input type=button class=bigbutton1 value=Food onclick=foodlist() Button>\r\n"+
"<input type=button class=bigbutton2 value=Drink onclick=drinklist() Button>\r\n"+
"</div>\r\n"+
"<div id=centerDoc>\r\n"+
"<p id=phrase></p>\r\n"+
"</div>\r\n"+
"</body>\r\n"+
"</html>\r\n" +
            "\r\n";
            return htmlpage;
}

void lcdtampilan1(){
  
    lcd.clear();
    lcd.print("Halo Selamat");
    lcd.setCursor(0,1);
    lcd.print("Datang");
    delay(1500);
    lcd.clear();
    lcd.print("SSID : NuMenu");
    lcd.setCursor(0,1);
    lcd.print("pass : password");
    delay(1500);
    lcd.clear();
    lcd.print("IP Address : ");
    lcd.setCursor(0,1);
    lcd.print("192.168.4.1");
    delay(1500);
}
void lcdtampilan2(){
   
   while (kondisi == 1){
     if (digitalRead(5) == HIGH)
      {kondisi = kondisi + 1;}
    lcd.clear();
    lcd.print("Makanan : ");
    lcd.setCursor(0,1);
    lcd.print(makanan);
    delay(1500);
    lcd.clear();
    lcd.print("Minuman : ");
    lcd.print(minuman);   
    delay(1500);
    lcd.clear();
    lcd.print("CashBack : ");
    lcd.setCursor(0,1);
    lcd.print("Rp. "+ cashback);
    delay(1500);
    lcd.clear();
    lcd.print("Terimakasih");
    lcd.setCursor(0,1);
    lcd.print("Tunggu Bentar");
    delay(1500);}
    
    while(kondisi == 2){
   if (digitalRead(5) == HIGH)
      {kondisi = kondisi + 1;}
    lcd.clear();
    lcd.print("Selamat Makannnn");
    lcd.setCursor(0,1);
    lcd.print("XD"); 
    delay(1500);}
    while(kondisi == 3) {
    if (digitalRead(5) == HIGH)
      {kondisi = kondisi + 1;}
    lcd.clear();
    lcd.print("Selamat Tinggal");
    lcd.setCursor(0,1);
    lcd.print("Terimakasih");
    delay(1500);}
 
}
