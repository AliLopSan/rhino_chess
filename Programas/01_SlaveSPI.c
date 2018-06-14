//-----------------------------------------------------------------------------
//--------------------- Robótica Práctica 4: ----------------------------------
//               Comunicación SPI - Slave Program
//                           versión 1.0
//                  por Alitzel López Sánchez
//-----------------------------------------------------------------------------
// Idea: 
// Utilizando SPI, hacer que el Microcontrolador A despliegue la lectura de los
// dip switches del Microcontrolador B
//----------------------------------------------------------------------------

//--------------------- PIC CONFIGURATION  ----------------------------------
#include<16f877a.h>
#include<stdlib.h>
#include<stdio.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock = 20MHz)

//------------------------ PORT LABELING  -----------------------------------
#BYTE SSPSTAT = 0x94 
#BYTE SSPBUF  = 0x13
#BYTE SSPCON  = 0x14
#BYTE OPTION  = 0x81
#BYTE ADCON1  = 0x9F
#BYTE TRISA   = 0x85
#BYTE TRISB   = 0x86
#BYTE TRISD   = 0x88
#BYTE TRISC   = 0x87
#BYTE PORTB   = 0x06
#BYTE PORTD   = 0x08
#BYTE PORTC   = 0x07
#BYTE TMR0    = 0x01

#BIT SSPSTAT_BF = SSPSTAT.0
#BIT RBPU       = OPTION.7
#BIT TRISA5     = TRISA.5
#BIT TRISC3     = TRISC.3
#BIT TRISC5     = TRISC.5
#BIT TRISC7     = TRISC.7
#BIT RC7       = PORTC.7
#BIT LED        = PORTD.3

//------------------------ NEW DATA TYPES -----------------------------------
typedef enum
{
  SPI_MASTER_OSC_DIV4  = 0b00100000,
  SPI_MASTER_OSC_DIV16 = 0b00100001,
  SPI_MASTER_OSC_DIV64 = 0b00100010,
  SPI_MASTER_TMR2      = 0b00100011,
  SPI_SLAVE_SS_EN      = 0b00100100,
  SPI_SLAVE_SS_DIS     = 0b00100101
}Spi_Type;

typedef enum
{
  SPI_DATA_SAMPLE_MIDDLE = 0b00000000,
  SPI_DATA_SAMPLE_END    = 0b10000000
}Spi_Data_Sample;

typedef enum
{
  SPI_CLOCK_IDLE_HIGH = 0b00001000,
  SPI_CLOCK_IDLE_LOW  = 0b00000000
}Spi_Clock_Idle;

typedef enum
{
  SPI_IDLE_2_ACTIVE = 0b00000000,
  SPI_ACTIVE_2_IDLE = 0b01000000
}Spi_Transmit_Edge;



//----------------------  FUNCTION PROTOTYPES ------------------------------ 
void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge);
static void spiReceiveWait();
unsigned spiDataReady();
void spiWrite(char dat);
char spiRead();


//----------------------      MAIN       ------------------------------------
void main(void)
{
   TRISB  = 0xFF;
   TRISD  = 0x00;
   PORTD  = 0x00;
   
   ADCON1 = 0x07;
   TRISA5 = 1;
   
   spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
   
   while(TRUE)
   {
      if(spiDataReady())
      {
         LED = 1;
         delay_ms(1000);
         LED = 0;
      }

   }   
   
}

//-----------------------   FUNCTION AREA ------------------------------------

void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
  TRISC5 = 0;
  if(sType & 0b00000100) //If Slave Mode
  {
    SSPSTAT = sTransmitEdge;
    TRISC3 = 1;
  }
  else //If Master Mode
  {
    SSPSTAT = sDataSample || sTransmitEdge;
    TRISC3 = 0;
  }
  SSPCON = sType || sClockIdle;
}

static void spiReceiveWait()
{
  while ( !SSPSTAT_BF ); // Wait for Data Receipt complete
}

unsigned spiDataReady() //Check whether the data is ready to read
{
  if(SSPSTAT_BF)
    return 1;
  else
    return 0;
}

void spiWrite(char dat) //Write data to SPI bus
{
  SSPBUF = dat;
}

char spiRead()    // Read the received data
{
  spiReceiveWait();      // Wait until all bits receive
  return(SSPBUF); // Read the received data from the buffer
}


