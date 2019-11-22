#define uchar unsigned char
#define uint  unsigned int  

char QTI1=11,QTI2=12,QTI3=6,QTI4=10,
      motor_left=5,motor_right=9;
 uchar number=0,turn=0,qtis;
char route[35]={1,2,2,1,1, 1,1,1,1,2, 2,2,0,1,2,  
                  1,1,0,2,1, 2,1,1,2,0, 1,1,1,1,1, 1,1,1,2,1};//前进为0，左转为1，右转为2。数组route用于规划机器人转弯策略。 
	       
void setup() 
{
  //设定串口通信波特率为9600
  Serial.begin(9600);
  //设定4、5、6、7引脚为QTI输入引脚.
  pinMode(QTI1,INPUT);  
  pinMode(QTI2,INPUT); 
  pinMode(QTI3,INPUT); 
  pinMode(QTI4,INPUT); 
  //设置2、3引脚为电机输出引脚.
  pinMode(motor_left ,OUTPUT); 
  pinMode(motor_right,OUTPUT);
}
//微前进函数
void forward_m()
{
    //Set 3 pins to high level.
    digitalWrite(motor_left,HIGH);
    //Delay 1300 us
    delayMicroseconds(1600);
    //Set 3 pins to low level.
    digitalWrite(motor_left,LOW);
    //Set 3 pins to high level.
    digitalWrite(motor_right,HIGH);
    //Delay 1700 us
    delayMicroseconds(1400);
    //Set 4 pins to low level.
    digitalWrite(motor_right,LOW);
    //Delay of 20 ms.
    delay(20);
 }
 //前进函数
 void forward(int i)
 {
   int j;
   for(j=0;j<i;j++)
     forward_m();
 }
//微右转函数
 void Turn_right_m()
 {
  //Set 3 pins to high level.
  digitalWrite(motor_left,HIGH);
  //Delay 1300 us
  delayMicroseconds(1550);
  //Set 3 pins to low level.
  digitalWrite(motor_left,LOW);
  //Set 3 pins to high level.
  digitalWrite(motor_right,HIGH);
  //Delay 1700 us
  delayMicroseconds(1550);
  //Set 4 pins to low level.
  digitalWrite(motor_right,LOW);
  //Delay of 20 ms.
  delay(10);
} 
//右转90度函数
void Turn_right_90()
{
  uchar j;
  for(j=0;j<28;j++)
  {
  digitalWrite(motor_left,HIGH); 

    delayMicroseconds(1570);                                                                                                                                                  

    digitalWrite(motor_left,LOW);

    digitalWrite(motor_right,HIGH);
  
    delayMicroseconds(1570);

    digitalWrite(motor_right,LOW);

    delay(20);
  }
}
//微左转函数
void Turn_left_m()
{
    //Set 3 pins to high level.
    digitalWrite(motor_left,HIGH); 
    //Delay 1300 us
    delayMicroseconds(1450);
    //Set 3 pins to low level.
    digitalWrite(motor_left,LOW);
    //Set 3 pins to high level.
    digitalWrite(motor_right,HIGH);
    //Delay 1700 us
    delayMicroseconds(1450);
    //Set 4 pins to low level.
    digitalWrite(motor_right,LOW);
    //Delay of 20 ms.
    delay(10);
}
//左转90度函数
void Turn_left_90()
{
  uchar j;
  for(j=0;j<26;j++)
    {
   
    digitalWrite(motor_left,HIGH); 

    delayMicroseconds(1430);

    digitalWrite(motor_left,LOW);

    digitalWrite(motor_right,HIGH);
  
    delayMicroseconds(1430);

    digitalWrite(motor_right,LOW);

    delay(20);
    }
}
//后转函数
void Turn_back()
{
  uchar j;
  for(j=0;j<45;j++)
    {
   
    digitalWrite(motor_left,HIGH); 

    delayMicroseconds(1400);

    digitalWrite(motor_left,LOW);

    digitalWrite(motor_right,HIGH);
  
    delayMicroseconds(1400);

    digitalWrite(motor_right,LOW);

    delay(20);
    }
    
    QTI();
    
}
void QTI()
{
    qtis=digitalRead(QTI1)*8+digitalRead(QTI2)*4
             +digitalRead(QTI3)*2+digitalRead(QTI4);
      while(qtis==0)
      {
        qtis=digitalRead(QTI1)*8+digitalRead(QTI2)*4
             +digitalRead(QTI3)*2+digitalRead(QTI4);
        forward_m();
        delay(1);
      }
 }
void loop() 
{
      qtis=digitalRead(QTI1)*8+digitalRead(QTI2)*4
             +digitalRead(QTI3)*2+digitalRead(QTI4);
          Serial.println(qtis);   
        switch(qtis)
        {
          case 1 :                               //0001
          case 3 : Turn_right_m();break;//微右转 //0011 
          
          case 8 :                               //1000
          case 12: Turn_left_m();break; //微左转 //1100   
          
          case 2 :                               //0010
          case 4 :                               //0100
          case 5 :                               //0101
          case 6 :                               //0110
          case 9 :                               //1001
          case 10:                               //1010
          case 11:                               //1011
          case 13: forward_m();break;   //前进   //1101
        }  
     if(qtis==0)		   //如果4个QTI全部检测为白，则执行以下语句
     {	
        	number++;
        	if(turn>34)
         {
           forward(20);
           while(1);
          }     	
        	if(number>8)	   //连续2两次检测到全白   
        	 {  
        	  Turn_back();		//后转
            delay(50);
        	  number=0;
        	 }
    	}
      if(qtis==7 || qtis==14 || qtis==15)	   //4个QTI至少3个检测到黑，则执行转弯语句
    		{
    			 delay(5);
           forward(2);
           qtis=digitalRead(QTI1)*8+digitalRead(QTI2)*4
             +digitalRead(QTI3)*2+digitalRead(QTI4);  
           if(qtis==7 || qtis==14 || qtis==15)    //4个QTI至少3个检测到黑，则执行转弯语句
           {
                switch(route[turn])
                {
                  case 0:forward(15);break;
                  case 1:forward(12);Turn_left_90();break;
                  case 2:forward(13);Turn_right_90();break;
                }
              
                turn++;
            }         		  
    		}		

}
