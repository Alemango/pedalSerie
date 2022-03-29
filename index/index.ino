#define botonIterar 35
#define botonConfirmar 34
#define botonAscendente 32
#define botonDescendente 33
#define botonPlay 27

#define ledAlabanza 2
#define ledAdoracion 4
#define ledPropias 17
#define ledClick 18

#define minAlabanza 1
#define maxAlabanza 35
#define minAdoracion ( maxAlabanza + 1 )
#define maxAdoracion ( minAdoracion + 15 )
#define minPropias ( maxAdoracion + 1 )
#define maxPropias ( minPropias + 8)
#define click ( maxPropias + 1 )

byte controlSeccion;
byte escenaFila;

bool estadoClick = false;
bool estadoEscena = false;
bool estadoPlay = false;

void setup(){
    Serial.begin(115200);

    pinMode(botonIterar, INPUT);
    pinMode(botonConfirmar, INPUT);
    pinMode(botonAscendente, INPUT);
    pinMode(botonDescendente, INPUT);

    pinMode(ledAlabanza, OUTPUT);
    pinMode(ledAdoracion, OUTPUT);
    pinMode(ledPropias, OUTPUT);
    pinMode(ledClick, OUTPUT);
}

void loop(){    
    controlSeccion = columnaIterador(controlSeccion);
    
    switch (controlSeccion)
    {
        case 1:{
            digitalWrite(ledAlabanza, HIGH);
            apagarLEDS(controlSeccion);
            limitesSeccion(controlSeccion);
            break;
        }
        case 2:{
            digitalWrite(ledAdoracion, HIGH);
            apagarLEDS(controlSeccion);
            limitesSeccion(controlSeccion);
            break;
        }
        case 3:{
            digitalWrite(ledPropias, HIGH);
            apagarLEDS(controlSeccion);
            limitesSeccion(controlSeccion);
            break;
        }
        case 4:{
            digitalWrite(ledClick, HIGH);
            apagarLEDS(controlSeccion);
            limitesSeccion(controlSeccion);
            break;
        }
        case 5:{
            digitalWrite(ledAlabanza, HIGH);
            apagarLEDS(controlSeccion);
            limitesSeccion(controlSeccion);
            break;
        }
        default:{
            break;
        }
    }
}

byte columnaIterador(byte iteradorColumna){
    if(iteradorColumna < 1 || iteradorColumna > 4){
        iteradorColumna = 1;
    }

    if(digitalRead(botonIterar) == HIGH){
        iteradorColumna++;
        byte pasosMover;
        delay(350);

        if(iteradorColumna == 1 || iteradorColumna == 5){
            pasosMover = restaEscena(iteradorColumna);
            pasosEscenaArriba(pasosMover);
            escenaFila = minAlabanza;
        }
        else if(iteradorColumna == 2){
            pasosMover = restaEscena(iteradorColumna);
            pasosEscenaBajo(pasosMover);
            escenaFila = minAdoracion;
        }
        else if(iteradorColumna == 3){
            pasosMover = restaEscena(iteradorColumna);
            pasosEscenaBajo(pasosMover);
            escenaFila = minPropias;
        }
        else if(iteradorColumna == 4){
            pasosMover = restaEscena(iteradorColumna);
            pasosEscenaBajo(pasosMover);
            escenaFila = click;
        }
    }

    return iteradorColumna;
}

void apagarLEDS(byte seleccion){
    if(seleccion == 1 || seleccion == 5){
        digitalWrite(ledAdoracion, LOW);
        digitalWrite(ledPropias, LOW);
        digitalWrite(ledClick, LOW);
    }
    else if(seleccion == 2){
        digitalWrite(ledAlabanza, LOW);
        digitalWrite(ledPropias, LOW);
        digitalWrite(ledClick, LOW);
    }
    else if(seleccion == 3){
        digitalWrite(ledAlabanza, LOW);
        digitalWrite(ledAdoracion, LOW);
        digitalWrite(ledClick, LOW);
    }
    else if(seleccion == 4){
        digitalWrite(ledAlabanza, LOW);
        digitalWrite(ledAdoracion, LOW);
        digitalWrite(ledPropias, LOW);
    }
}

void botonesEscena(){
    if (digitalRead(botonAscendente) == HIGH){
        Serial.write(144);
        Serial.write(1);
        Serial.write(100);

        delay(200);

        escenaFila++;
    }
    else if (digitalRead(botonDescendente) == HIGH){
        Serial.write(144);
        Serial.write(2);
        Serial.write(100);

        delay(200);

        escenaFila--;
    }
    else if(digitalRead(botonConfirmar) == HIGH){
        if (estadoEscena == false){
        Serial.write(144);
        Serial.write(3);
        Serial.write(100);

        delay(200);

        estadoEscena = true;
        estadoPlay = true;
        }
        else if (estadoEscena == true){
          Serial.write(144);
          Serial.write(4);
          Serial.write(100);

          delay(200);

          estadoEscena = false;
        }
    }
    else if (digitalRead(botonPlay) == HIGH){
        if (estadoPlay == false){
            Serial.write(144);
            Serial.write(5);
            Serial.write(100);

            delay(200);

            estadoPlay = true;
        }
        else if (estadoPlay == true){
            Serial.write(144);
            Serial.write(6);
            Serial.write(100);

            delay(200);

            estadoPlay = false;
        }
    }
}

void limitesSeccion(byte columnaSeleccionada){

    if(columnaSeleccionada == 1 || columnaSeleccionada == 5){
        if (escenaFila >= minAlabanza && escenaFila <= maxAlabanza){
            botonesEscena();
        }
        else if (escenaFila > maxAlabanza){
            controlSeccion = 2;
        }
    }
    else if(columnaSeleccionada == 2){
        if (escenaFila >= minAdoracion && escenaFila <= maxAdoracion){
            botonesEscena();
        }
        else if (escenaFila > maxAdoracion){
            controlSeccion = 3;
        }
        else if (escenaFila < maxAdoracion){
            controlSeccion = 1;
        }
    }
    else if(columnaSeleccionada == 3){
        if (escenaFila >= minPropias && escenaFila <= maxPropias){
            botonesEscena();
        }
        else if (escenaFila > maxPropias){
            controlSeccion = 1;
        }
        else if (escenaFila < maxPropias){
            controlSeccion = 2;
        }
    }
    else if(columnaSeleccionada == 4){
        if (escenaFila == click){
            botonesClick();
        }
    }
}

byte restaEscena(byte seccion){
    byte pasos;

    if(seccion == 1 || seccion == 5){
        pasos = click - 1;
    }
    else if(seccion == 2){
        pasos = minAdoracion - escenaFila;   
    }
    else if(seccion == 3){
        pasos = minPropias - escenaFila;
    }
    else if(seccion == 4){
        pasos = click - escenaFila;
    }

    return pasos;
}

void pasosEscenaBajo(byte escenas){
    byte i;

    for(i = 0; i < escenas; i++){
        Serial.write(144);
        Serial.write(1);
        Serial.write(100);
        delay(10);
    }
}

void pasosEscenaArriba(byte escenas){
    byte i;

    for(i = 0; i < escenas; i++){
        Serial.write(144);
        Serial.write(2);
        Serial.write(100);
        delay(10);
    }
}

void botonesClick(){
    if (digitalRead(botonAscendente) == HIGH){
        Serial.write(176);
        Serial.write(14);
        Serial.write(1);

        delay(200);
    }
    else if (digitalRead(botonDescendente) == HIGH){
        Serial.write(176);
        Serial.write(14);
        Serial.write(127);

        delay(200);
    }
    else if(digitalRead(botonConfirmar) == HIGH){
        if (estadoClick == true){
            Serial.write(176);
            Serial.write(15);
            Serial.write(1);
      
            delay(200);

            estadoClick = false;
        }
      else if (estadoClick == false){
            Serial.write(176);
            Serial.write(15);
            Serial.write(127);
      
            delay(200);

            estadoClick = true;
      }
    }
}
