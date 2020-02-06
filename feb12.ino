int IR1 = 2;
int IR2 = 3;
int IR3 = 4;
int IR4 = 5;
int IR5 = 6;
int MOT_R1 = 11;
int MOT_R2 = 12;
int MOT_L1 = 9;
int MOT_L2 = 10;
int rf1 = 7;
int rf2 = 8;
int m,n,o,x,y,reg,count_m,count_n,RLT,s,t,u;
int t_check = 0;
int prev_m = 0;
int prev_n = 0;
int left,right,middle,l_middle,r_middle,i,a;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
    pinMode(rf1,INPUT);
    pinMode(rf2,INPUT);
    pinMode(IR1, INPUT); //make IR1 INPUT pin
    pinMode(IR2, INPUT); //make IR2 INPUT pin
    pinMode(IR3, INPUT); //make IR3 INPUT pin
    pinMode(IR4, INPUT); //make IR3 INPUT pin
    pinMode(IR5, INPUT); //make IR3 INPUT pin
    pinMode(MOT_R1, OUTPUT); //make MOT_R1 OUTPUT pin
    pinMode(MOT_R2, OUTPUT); //make MOT_R2 OUTPUT pin
    pinMode(MOT_L1, OUTPUT); //make MOT_L1 OUTPUT pin
    pinMode(MOT_L2, OUTPUT); //make MOT_L2 OUTPUT pin
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("SOurce");
  Serial.println(" ");
  Serial.print("prev_m = ");
Serial.print(prev_m);
Serial.println("");
Serial.println("prev_n =");
Serial.print(prev_n);
Serial.println("reg = ");
Serial.println(reg);
Serial.println("");
  Serial.println("count_m = ");
Serial.print(count_m);
Serial.println("");
Serial.println("count_n = ");
Serial.print(count_n);
Serial.println("");
Serial.println("o = ");
Serial.print(o);
while(reg ==0)
  {
    x =digitalRead(rf1);
    y =digitalRead(rf2);
a = read_co(m,n,o);
        Serial.println("Ivide keri");
        count_m = 0;
        count_n = 0;
switch(a)
{
 case 0: {
         m = 0;
         n = 0;
         o = 0;
         reg = 0;
         delay(10);
         break;
        } 
 case 1:
        {
         m = 2;
         n = 1;
         reg = 1;
         delay(10);
         break;
        } 
 case 2:
        {
         m = 1;
         n = 3;
         reg = 1;
         delay(10);
         break;
        } 
 case 3:
        {
         m = 4;
         n = 3;
         reg = 1;
         delay(10);
         break;
        } 
}
Serial.println("m = ");
Serial.print(m);
Serial.println("");
Serial.println("n = ");
Serial.print(n);
Serial.println("");
Serial.println("o = ");
Serial.print(o);
Serial.println("");
Serial.println("a = ");
Serial.print(a);
Serial.println("");
Serial.println("reg");
Serial.print(reg);
Serial.println("");
Serial.println("//-----//");
  }
  while(reg == 1)
  {
   if(t_check == 1)
   {
    count_m = m - prev_m;
   count_n = n - prev_n;
   o = count_n;
   prev_m = m;
   prev_n = n;
    count_n = count_m;
    count_m = o;
    o = count_n;
   }
   else
   {
    count_m = m - prev_m;
   count_n = n - prev_n;
   o = count_n;
   prev_m = m;
   prev_n = n;
   }
    if(count_m<0)
   {
    count_m = (-1*count_m); 
    reg = 2;
    RLT = 1;
 }
    if(count_n<0)
   {
    count_n = (-1*count_n);
    o = count_n;
    reg = 2;
    RLT =1;
   }
   else
   {
   RLT = 0;
   reg = 2;
   }
 break;}
if(reg == 2)
{
 count_n = count_n + 1;
 o = count_n;
 reg = 3; 
}
Serial.println(""); 
  readSensor(); //read sensor data
      while((count_m==0)&&(count_n==0))
  {
    reg = 0;
      a = 0;
      if((o!=0)&&(t_check==0))
      {
      t_check = 1;
      }
      else if((o!=0)&&(t_check==1))
      {
       t_check = 0; 
      }
      else
      {
       t_check = t_check; 
      }
   readSensor(); //read sensor data
   Serial.println("stop--");
   stop_mot(); //stop rotation of motors
   delay(10);
   break;
   }

  while((reg==3)&&(count_m>0)&&(count_n==o))
  {
   readSensor(); //read sensor data
   forward(); //move forward
   delay(1); //delay of 1 millisecond
   if((right==0)&&(middle==0)&&(left==0))
   {
   Serial.println("m execute akunnu--");
   count_m--;
   stop_mot(); //stop rotation of motors
    Serial.println("forward");
    while((right||left||middle)!=1)
    {
      readSensor(); //read sensor data
      Serial.println("forward in loop");
 digitalWrite(MOT_R1,HIGH); //Write HIGH to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,HIGH);//Write HIGH to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(10); //delay of 5 millisecond
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW);//Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
    }
   }
  }
  while((reg==3)&&(count_m==0)&&(count_n==o)&&(o!=0))
  {
    if((RLT == 0)&&(t_check==0))
    {
    reg = 4;
    readSensor(); //read sensor data
    Serial.println("n1 execute akunnu--");
    turn_left();
    delay(1); //delay of 1 millisecond
    }
    else if((RLT == 1)&&(t_check==0))
    {
     reg = 4;
    readSensor(); //read sensor data
    Serial.println("n1 execute akunnu--");
    turn_right();
    RLT = 0;
    delay(1); //delay of 1 millisecond 
    }
        else if((RLT == 0)&&(t_check==1))
    {
     reg = 4;
    readSensor(); //read sensor data
    Serial.println("n1 execute akunnu--");
    turn_right();
    RLT = 0;
    delay(1); //delay of 1 millisecond 
    }
    else
    {
    reg = 4;
    readSensor(); //read sensor data
    Serial.println("n1 execute akunnu--");
    turn_left();
    delay(1); //delay of 1 millisecond 
    }
  }
  while((reg==4)&&(count_m==0)&&(count_n!=o)&&(count_n>0))
  {
   readSensor(); //read sensor data
   Serial.println("n2 execute akunnu--");
   forward(); //move forward
   delay(1);  //delay of 1 millisecond
   if((right==0)&&(middle==0)&&(left==0))
   {
   count_n--;
   stop_mot(); //stop rotation of motors
    Serial.println("forward");
    while((right||left||middle)!=1)
   {
 readSensor(); //read sensor data
 Serial.println("forward in loop");
 digitalWrite(MOT_R1,HIGH); //Write HIGH to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,HIGH);//Write HIGH to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(10); //delay of 5 millisecond
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW);//Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
    }
   }
  }

}

void forward()
{
 readSensor(); //read sensor data
 if ((r_middle==1)&&(middle==0)&&(l_middle==1)&&((left||right)==1))
 {
  Serial.println("forward");
 digitalWrite(MOT_R1,HIGH); //Write HIGH to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,HIGH);//Write HIGH to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(10); //delay of 5 millisecond
 digitalWrite(MOT_R1,LOW);  //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW);//Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
 }
 else if ((r_middle==0)&&(middle==1)&&(l_middle==1)&&((left||right)==1))
 {
 Serial.println("left");
 digitalWrite(MOT_R1,HIGH); //Write HIGH to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW); //Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW); //Write LOW to MOT_L2
 delay(10); //delay of 2 millisecond
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW); //Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW); //Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
}
else if ((r_middle==1)&&(middle==1)&&(l_middle==0)&&((left||right)==1))
 {
 Serial.println("right");
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,HIGH); //Write HIGH to MOT_L1
 digitalWrite(MOT_L2,LOW); //Write LOW to MOT_L2
 delay(10); //delay of 2 millisecond
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW);//Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
}
else if((r_middle==1)&&(middle==0)&&(l_middle==0)&&((left||right)==1))
 {
  Serial.println("forward");
 digitalWrite(MOT_R1,HIGH); //Write HIGH to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,HIGH);//Write HIGH to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(10); //delay of 2 millisecond
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW);//Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW);//Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
 }
 else if((r_middle==0)&&(middle==0)&&(l_middle==1)&&((left||right)==1))
 {
  Serial.println("forward");
 digitalWrite(MOT_R1,HIGH); //Write HIGH to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,HIGH);//Write HIGH to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(10); //delay of 2 millisecond
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW);//Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
 }
return; 
}

void stop_mot()
{
 Serial.println("stopped");
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW);//Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW);//Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
 return;
}

void turn_left()
{
    for(i=0;i<5;i++)
  { delay(500); //delay of 2 millisecond
 digitalWrite(MOT_R1,HIGH); //Write HIGH to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW); //Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW); //Write LOW to MOT_L2
 delay(100); //delay of 2 millisecond
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW); //Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW); //Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
  }
 count_n--;
}

void turn_right()
{
    for(i=0;i<5;i++)
  { delay(500); //delay of 2 millisecond
 digitalWrite(MOT_R1,LOW); //Write HIGH to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,HIGH); //Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW); //Write LOW to MOT_L2
 delay(100); //delay of 2 millisecond
 digitalWrite(MOT_R1,LOW); //Write LOW to MOT_R1
 digitalWrite(MOT_R2,LOW); //Write LOW to MOT_R2
 digitalWrite(MOT_L1,LOW); //Write LOW to MOT_L1
 digitalWrite(MOT_L2,LOW); //Write LOW to MOT_L2
 delay(1); //delay of 1 millisecond
  }
 count_n--;
}

void readSensor()
{
  right = digitalRead(IR1); //read right sensor data
  r_middle = digitalRead(IR2); //read middle sensor data
  middle = digitalRead(IR3); //read middle sensor data
  l_middle = digitalRead(IR4); //read middle sensor data
  left = digitalRead(IR5); //read left sensor data
  Serial.print(right);
  Serial.print(',');
  Serial.print(middle);
  Serial.print(',');
  Serial.print(left);
  Serial.println();
  return; 
}
int read_co(int m, int n, int o)
{
 if ((x==0)&&(y==1))
{
 a = 1;
} 
else if((x==1)&&(y==0))
{
 a = 2; 
}
else if((x==1)&&(y==1))
{
 a=3; 
}
else
{
  a=0;
}
return(a);
}
