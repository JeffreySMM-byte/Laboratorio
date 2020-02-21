import serial
import tkinter as tk
import struct
import time

root = tk.Tk()

label1 = tk.Label(root, text="Voltaje Pot1")
label2 = tk.Label(root, text="Voltaje Pot2")
label5 = tk.Label(root, text="Valor de contador")
label6 = tk.Label(root, text="COM 12")
entry1 = tk.Entry(root)

def sendData():
    #serialPort.write((struct.pack('>B',255)))
    try:
        num = int(entry1.get())
        error.set("")
        if num<=255 and num>=0:
            serialPort.write(struct.pack('>B', num))
        else:
            error.set("Debe ingresar un numero entero")
    except:
        print("Ingrese el valor del contador")
        error.set("Debe ingresar un numero entero")

button1 = tk.Button(root, text="Enviar", command=sendData)

serialPort = serial.Serial(port = "COM12", baudrate=9600, timeout=1500)


def getdata():
    if ord(serialPort.read())==193:

        a1 = ord(serialPort.read())
        a2 = ord(serialPort.read())

        adc1 = "{0:.1f}".format(a1 * 5/255)
        adc2 = "{0:.1f}".format(a2 * 5/255)

        adc1 = str(adc1)
        adc2 = str(adc2)

        P1.set(adc1)
        P2.set(adc2)
    root.after(10, getdata)




P1 = tk.StringVar()
P1.set("0")
label3 = tk.Label(root, textvariable= P1)
label3.grid(row=1)


P2 = tk.StringVar()
P2.set("0")
label4 = tk.Label(root, textvariable= P2)
label4.grid(row=2)


error = tk.StringVar()
error.set("")
label7 = tk.Label(root, textvariable = error)
label7.grid(row=7)

label1.grid(row=1, column=3)
label2.grid(row=2, column=3)
label5.grid(row=5)

entry1.grid(row=6)
button1.grid(row=6, column=3)


root.after(10, getdata)
root.mainloop()



