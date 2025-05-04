#include<reg51.h>
void Serial_begin();
bit Seial_available();
void Serial_Princhar (unsigned char daata);
void Serial_printstr(char *str);
void intToStr(int num, char *str);


void Serial_begin() {
    TMOD = 0x20; // Timer1 in Mode 2
    TH1 = 0xFD;  // Load value for 9600 baud rate for 9600=FD,4800=DA,2400=F4,1200=E8
    SCON = 0x50; // Mode 1, 8-bit UART, enable receiver
    TR1 = 1;     // Start Timer1
}

 bit Serial_available() {
	 int x=RI;
    return (x); // Check if the receive interrupt flag is set
}

char Serial_read() {
    char received_byte = 0;
    if (RI) {
        RI = 0; // Clear the receive interrupt flag
        received_byte = SBUF; // Read the received byte
    }
    return received_byte;
}

// Function to transmit a single byte
void Serial_printchar(unsigned char daata)   //UART_TxChar
	{
    SBUF = daata;  // Load data into UART buffer
    while(TI == 0);  // Wait until transmission is complete
    TI = 0;  // Clear transmission flag
}

// Function to transmit a string
void Serial_printstr(char *str) {
    while(*str) {
        Serial_printchar(*str++);  // Transmit each character in the string
    }
}


void intToStr(int num, char *str) {
    int i, rem, len = 0;
    int n = num;

    // Calculate the length of the number
    while (n != 0) {
        len++;
        n /= 10;
    }

    // If the number is 0, set length to 1
    if (num == 0) {
        len = 1;
    }

    // Null terminate the string
    str[len] = '\0';

    // Extract each digit and convert to character
    for (i = len - 1; i >= 0; i--) {
        rem = num % 10;
        num = num / 10;
        str[i] = rem + '0';
    }
}

void main()
{  unsigned char a;
	unsigned int i;
	unsigned char str[6];
  Serial_begin();
	Serial_printstr("UART Serial communication with Microcontroller");
	Serial_printstr("\n");
	Serial_printstr("Enter Any Character");
	Serial_printstr("\n");
    while(1)
			{
			if(Serial_available())
			{
			a=Serial_read();
				Serial_printchar('\n');
			
					Serial_printchar('\n');
					Serial_printstr("Received data from key board =");
			Serial_printchar(a);
				Serial_printchar('\n');	
				Serial_printstr("Send data on PORT2=");
				Serial_printchar(a);
				P2=a;
					Serial_printchar('\n');
				if(a=='a')
				{
					P2=0xFF;
				}
				if(a=='b')
				{
					P2=0x00;
				}}}} 
	
	/*	#include <reg51.h>  // Include header file for AT89S52

void UART_Init() {
    TMOD = 0x20;    // Timer 1 in Mode 2, 8-bit auto-reload
    TH1 = 0xFD;     // Set baud rate to 9600 (for 11.0592 MHz crystal)
    SCON = 0x50;    // Mode 1, 8-bit UART, enable receiver
    TR1 = 1;        // Start Timer 1
}

void UART_Transmit(unsigned char ch) {
    SBUF = ch;      // Load the character into SBUF register
    while (TI == 0); // Wait for transmission to complete
    TI = 0;         // Clear TI flag for next transmission
}

void main() {
    UART_Init();    // Initialize UART
    UART_Transmit('A');  // Transmit character 'A'
    while(1);       // Infinite loop to keep the program running
}
*/