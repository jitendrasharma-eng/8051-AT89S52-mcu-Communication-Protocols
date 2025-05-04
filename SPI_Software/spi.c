/*
#include <reg51.h>

sbit cs = P1^3;
sbit clk = P1^0;
sbit dout = P1^2;  // MISO
sbit din = P1^1;   // MOSI

unsigned int spi_adc_value(void);
void delay(unsigned int i);

void main() {
    
    while(1) {
        P3 = spi_adc_value(); // Read ADC value and output to P3
    }
}

unsigned int spi_adc_value(void) {
    unsigned int temp=0;  // Initialize temp to 0
    char i;
    cs = 0;
    clk = 0; din = 1; clk = 1; // Start bit
    clk = 0; din = 1; clk = 1; // Single-ended
    
    clk = 0; din = 0; clk = 1; // d2
    clk = 0; din = 0; clk = 1; // d1
    clk = 0; din = 0; clk = 1; // d0
    
    clk = 0; din = 1; clk = 1; // t sample
    clk = 0; din = 1; clk = 1; // Null bit
    
    for(i = 11; i >= 0; i--) {
        clk = 0;
        if(dout == 1)
            temp |= (1 << i);
        clk = 1;
    }
    cs = 1;
    return temp;
}

void delay(unsigned int i) {
    unsigned int j;
    for(j = 0; j < i; j++);
}
*/

//CODE of lcd interfacing with 8051 microcontroller
#include<reg51.h>

void delay(unsigned int i);
void lcd_cmd(unsigned char a);
void lcd_data(unsigned char b);
void lcd_init(void);
void lcd_str(unsigned char *str);
unsigned int spi_adc_value(void);
void hex2ascii(unsigned char value);
sbit rs=P2^0;
sbit en=P2^1;
#define ldata P1  // sfr ldata =0xA0;
sbit clk=P3^0;
sbit din=P3^1;
sbit dout=P3^2;
sbit cs=P3^3;
void main()

{
	unsigned int temp;
lcd_init();
	lcd_str("   WELCOME TO   ");
	lcd_cmd(0xc0);
	lcd_str("   MY PROJECT   ");
	
	delay(65000*2);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
lcd_str("   SPI MODULE   ");
	lcd_cmd(0xc0);
	lcd_str("   INTERFACING   ");
		delay(65000*2);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
lcd_str(" SPI TEMP VALUE ");


	while(1){
	
	temp=spi_adc_value();//adc
		lcd_cmd(0xc0);
		temp=temp/8.5;
		hex2ascii(temp);
		//lcd_data(temp);
	
	}
}
void hex2ascii(unsigned char value)//0xff-255
{
	unsigned char x,d1,d2,d3;
	x=value/10;//25
	d3=value%10;//5
	d2=x%10;//5
	d1=x/10;//2
	lcd_data(d1+0x30);//asccii
lcd_data(d2+0x30);
	lcd_data(d3+0x30);


}

void lcd_init()
{
lcd_cmd(0x38);
	lcd_cmd(0x0c);
	lcd_cmd(0x01);
	lcd_cmd(0x80);


}
void delay(unsigned int i)
{
unsigned int j;
	for(j=0;j<i;j++);
}

void lcd_cmd(unsigned char a)
{
  rs=0;//cmd 
	ldata=a;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_data(unsigned char b)
{
  rs=1;//data 
	ldata=b;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_str(unsigned char *str)
{
while(*str)
{
	lcd_data(*str++);
}

}
unsigned int spi_adc_value(void)
{
	
	unsigned int temp=0;
	char i;
	cs=0;
	clk=0;din=1;clk=1;//start
	clk=0;din=1;clk=1;//single ended
	
	clk=0;din=0;clk=1;//d2
	clk=0;din=0;clk=1;//d1
	clk=0;din=0;clk=1;//d0
	
	clk=0;din=1;clk=1; //t sample 
	clk=0;din=1;clk=1; //nullbit 
/*	for(i=11;i>=0;i--)
	{		clk=0;
		rd_bit=dout;
		temp=temp<<1;
		temp=temp|rd_bit;
	
		clk=1;
	}*/
	//Or
	for(i=11;i>=0;i--)
	{		clk=0;
		if(dout==1)
			temp |=(1<<i);
		clk=1;
	}
	cs=1;
	return temp;
}