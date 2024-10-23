int rele = 6; 
int botao = 2;
int flag = 0;
void setup()
{
  pinMode(rele, OUTPUT); 
  pinMode (botao, INPUT_PULLUP);
}
void loop()
{    
	if(digitalRead(botao) == HIGH && flag == 0)
		{
		while(digitalRead(botao) == HIGH);
{
		digitalWrite(rele, HIGH);
		flag = 1;
		delay(200);
}
	}
	else if(digitalRead(botao) == HIGH && flag == 1)      
	{
		while(digitalRead(botao) == HIGH);
{
		digitalWrite(rele, LOW);
		flag = 0;
		delay(200);
}
	}
}