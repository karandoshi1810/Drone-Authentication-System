#include <SoftwareSerial.h>
#include <Servo.h>

// Configure software serial port
SoftwareSerial SIM900(7, 8);
SoftwareSerial BTSerial(9, 10); // RX | TX
Servo myservo;
String data="";
char c;
char d;
int i=1;
int pos = 0;
char ch;
String str = "";
String a = "";
String b = "";
String set_pw="";
String gate_pw="";
String number="";
String randNumber="";
void setup()
{
  // Arduino communicates with SIM900 GSM shield at a baud rate of 19200
  // Make sure that corresponds to the baud rate of your module
 
  SIM900.begin(19200);
  Serial.begin(9600);
  // Give time to your GSM shield log on to network
  delay(2000);
  Serial.begin(9600);
  BTSerial.begin(9600);
  Serial.begin(9600);
  randomSeed(analogRead(0));
  randNumber = random(9999999);
  Serial.println(randNumber);
  delay(1000);
}

void loop()
{
   
  Serial.println("Enter the Phone Number");
  while(BTSerial.available()==0)
  {
   
  }
  while(BTSerial.available()>0)
  {
      c=BTSerial.read();
      data=data+c;
  }
  int num = data.length()-3;
  if((data[0]=='$')&&(data[num]=='$'))
    {
    Serial.println(data);
    number= data.substring(1, data.length()-3)+"";
    Serial.println(number);
    Serial.println("Company Data :- "+number);
    GSM();
    Serial.println("-----------------------------------------------------------------");
    }
   data="";
   delay(2000);
   Serial.println("Enter the customer");
   while(BTSerial.available()==0)
   {
   
   }
   while(BTSerial.available()>0)
   {
      d=BTSerial.read();
      data=data+d;
   }
   int num1 = data.length()-3;
   if((data[0]=='#')&&(data[num1]=='#'))
    {
      Serial.println(data);
      gate_pw+= data.substring(1, data.length()-3)+"";
      Serial.println(gate_pw);
      Serial.println("Customer Data :- "+gate_pw);
      Serial.println("-----------------------------------------------------------------");
    }
    Serial.println("Company Password :-"+randNumber);
    Serial.println("Customer Password :-"+gate_pw);

    if(randNumber==gate_pw)
    {
        myservo.attach(6);  
        myservo.write(0);            
        delay(1000);                            
        myservo.write(130);
        delay(6000);
        myservo.write(0);            
        delay(1000);
        SIM900.print("AT+CMGF=1\r");
        delay(100);
        SIM900.println("AT + CMGS = \""+number+"\"");
        delay(100);
 
        SIM900.println("Your Delivery is Succesfull.");
        SIM900.println("                            -Thank You");
        delay(100);

       // End AT command with a ^Z, ASCII code 26
        SIM900.println((char)26);
        delay(100);
        SIM900.println();
        // Give module time to send SMS
        delay(5000);
        }

}



void GSM()
{
    SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.println("AT + CMGS = \""+number+"\"");
  delay(100);
 
 
  SIM900.println("Your Security Code is : "+ randNumber);
  SIM900.println("Please Enter Security Code This Format :- #Code# ");
  delay(100);


   // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26);
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000);
}
