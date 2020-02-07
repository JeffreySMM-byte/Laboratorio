inicio del ciclo principal{
    funcion de inicio de puertos\
    while(1){
        if(PORTDbits.RD0 == 1){
            Si el boton de inicio se oprime se inicia la secuencia de las
            leds y el display de siete segmentos.
            bandera = 1;
            while(bandera == 1){
                if(PORTDbits.RD1 == 1){
                    Funcion leds
                    Se incrementa una variable llamada leds1 y se revisa el
                    valor de esta en un switch y dependiendo del valor de la
                    variable ese sera el case que se active y cada case enciende
                    uno de los bits del puerto indicado.
                           
                }
                if(PORTDbits.RD2 == 1){
                    Funcion leds2
                    Se ejecuta de la misma manera que la funcion leds
                }
                if(PORTDbits.RD6 == 1){
                    PORTC = se muestra el valor del numero 1 en hexadecimal en el display de siete segmentos
                }
                if(PORTDbits.RD7 == 1){
                    PORTC = se muestra el valor del numero 2 en hexadecimal en el display de siete segmentos
            }
        }
    }
        return
}