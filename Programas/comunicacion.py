#/////////////////////////////////////////////////////////////////////////////
#                   PRUEBA DE COMUNICACIÓN SERIAL
#                           version 1.0
#/////////////////////////////////////////////////////////////////////////////
# Descripción:
# En este programa mandamos números del 0 al 63 con 0 al final y luego del
# 63 al 127 con un 1 al final.

#Cómo usar git también
#---------------------------------------------------------------------------
import serial
import sys
import numpy
#----------------------------------------------------------------------------
#                           FUNCIONES
#----------------------------------------------------------------------------

# Open Serial Port
#***************************************************
def Serial_Port_Open():
    UART       = serial.Serial()
    UART.port  = '/dev/ttyUSB0'
    UART.open()
    # Default:
    # bytesize = EIGHTBITS,
    # parity   = PARITY_NONE
    # stopbits = STOPBITS_ONE
    # timeout  = None
    # xonxoff  = False  -> Disable software flow control
    # rtscts   = False  > Disable hardware flow control (RTS/CTS)
    # dsrdtr   = False
    # inter_byte_timeout = None
    #Read at least one character, wait indefinetly
    #write_timeout=None
    #timeout = None: wait forever / until requested number of bytes are received

    if( UART.is_open):
        print(" ttyUSB0 Opened Successfully... \n")
        print(UART)
        print("\n")

    else:
        print(" Error! in Opening ttyUSB0 \n")
        sys.exit("\n********** Sorry ****************\n")


#---------------------------------------------------------------------------
# GLOBAL VARIABLES
#---------------------------------------------------------------------------
Ts  = 0.005
ppr = 1572 #Para el motor grande
pi_ = 3.141593
kp  = 5
ki  = 0.0
kd  = 0.0
fte = 10
cpH = 1.5


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#                              MAIN
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
print("\n------------------------------------------------------------")
print("\t\t SERIAL BASE TO PYTHON")
print("--------------------------------------------------------------\n")

UART       = serial.Serial()
UART.port  = '/dev/ttyUSB0'
UART.open()

if( UART.is_open):
    print(" ttyUSB0 Opened Successfully... \n")
    print(UART)
    print("\n")
else:
    print(" Error! in Opening ttyUSB0 \n")
    sys.exit("\n********** Sorry ****************\n")


print("\n--------- Empezando Recepción / Envío ------------")
UART.flushInput()
print("Flush input")

print("This example writes to PIC: ")

flag = 0
while(1):
    if (flag == 0):
        for i in range(0,63):
            pwm    = bytes(i)
            print("\tSending : ",i," : ",pwm,"\n")
            UART.write(pwm)

            UART.flushOutput()

        for e in range(63,127):
            n   = e + 128
            pwm = bytes(n)
            print("\tSending : ",n," : ",pwm,"\n")
            UART.write(pwm)
            UART.flushOutput()


    else:
        break
