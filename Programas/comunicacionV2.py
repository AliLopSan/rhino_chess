#/////////////////////////////////////////////////////////////////////////////
#                   PRUEBA DE COMUNICACIÓN SERIAL
#                           version 1.0
#/////////////////////////////////////////////////////////////////////////////
# Descripción:
#   Envia y resive datos por comunicación serial rs232 

#-----------Librerias

import serial
import sys
import numpy

UART            = serial.Serial()
UART.buadrate   = 11250           #VELOCIDAD DE COMUNICACIÓN
UART.serial     = '/dev/ttyUSB0'  #RUTA DEL MODULO
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

print("------Iniciando Comunicación------")
print("\n")

reset_input_buffer()

s = int(input())
UART.write(s)

r = UART.read(size = 8)
print("\n Data in: \n", r)

reset_output_buffer()    