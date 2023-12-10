#from mfrc522 import MFRC522
#import utime

#reader = MFRC522(spi_id=0,sck=2,miso=4,mosi=3,cs=1,rst=0)

#print("Bring TAG closer...")
#print("")


#while True:
#    reader.init()
#    (stat, tag_type) = reader.request(reader.REQIDL)
#    if stat == reader.OK:
#        (stat, uid) = reader.SelectTagSN()
#        if stat == reader.OK:
#            card = int.from_bytes(bytes(uid),"little",False)
#            print("CARD ID: "+str(card))
#utime.sleep_ms(500)

from mfrc522 import MFRC522
from machine import UART
import utime

# Configuración del lector RFID
reader = MFRC522(spi_id=0, sck=2, miso=4, mosi=3, cs=1, rst=0)

# Configuración de la comunicación UART para enviar
uart_send = UART(0, baudrate=1000000, tx=12, rx=13 )  # Ajusta los pines tx y rx según tu configuración

print("Bring TAG closer...")
print("")

while True:
    reader.init()
    (stat, tag_type) = reader.request(reader.REQIDL)

    if stat == reader.OK:
        (stat, uid) = reader.SelectTagSN()

        if stat == reader.OK:
            card_id = int.from_bytes(bytes(uid), "little", False)
            print("CARD ID:", card_id)

            # Envía el ID por UART
            uart_send.write("{}".format(card_id))


    utime.sleep_ms(500)