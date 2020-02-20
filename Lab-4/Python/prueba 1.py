import serial
from tkinter import*
import struct
import time


serialPort = serial.Serial(port = "COM4", baudrate=9600, bytesize=8, timeout=2, stopbits=serial.STOPBITS_ONE)


while(1):
    if(serialPort.in_waiting > 0):

        serialString = serialPort.readline()
        print(serialString.decode('Ascii'))
        serialPort.write(b"Thank you for sending data \r\n")



root = Tk()

label1 = Label(root, text="Voltaje Pot1")
label2 = Label(root, text="Voltaje Pot2")
label3 = Label(root, text="pot1")
label4 = Label(root, text="pot2")
label5 = Label(root, text="Valor de contador")
entry1  = Entry(root)
button1 = Button(root, text="Enviar")

label1.grid(row=1, column=3)
label2.grid(row=2, column=3)
label3.grid(row=1)
label4.grid(row=2)
label5.grid(row=5)
entry1.grid(row=6)
button1.grid(row=6, column=3)

root.mainloop()



