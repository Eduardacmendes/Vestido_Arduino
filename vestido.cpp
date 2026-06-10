#include <Servo.h>

#define BOTAO 0

// pinos dos LEDs
int leds[] = {4, 1, 2, 7, 12, 13};
int numLeds = 6;

// pinos dos servos (grupo 1 e 2)
int servosGrupo1Pins[] = {3, 5, 6};
int servosGrupo2Pins[] = {9, 10, 11};

Servo servosGrupo1[3];
Servo servosGrupo2[3];

bool ligado = false;
int ultimoEstado = HIGH;

int angulo1 = 0, incremento1 = 1;
int angulo2 = 0, incremento2 = 1;
int grupo = 1;

void setup() {
    // inicializa LEDs
    for (int i = 0; i < numLeds; i++) {
        pinMode(leds[i], OUTPUT);
    }

    // inicializa servos grupo 1
    for (int i = 0; i < 3; i++) {
        servosGrupo1[i].attach(servosGrupo1Pins[i]);
        servosGrupo1[i].write(angulo1);
    }

    // inicializa servos grupo 2
    for (int i = 0; i < 3; i++) {
        servosGrupo2[i].attach(servosGrupo2Pins[i]);
        servosGrupo2[i].write(angulo2);
    }

    pinMode(BOTAO, INPUT_PULLUP);
}

void loop() {
    int leitura = digitalRead(BOTAO);

    // alterna estado do botão
    if (leitura == LOW && ultimoEstado == HIGH) {
        ligado = !ligado;
        delay(300); // debounce simples
    }
    ultimoEstado = leitura;

    if (ligado) {
        // acende todos os LEDs
        for (int i = 0; i < numLeds; i++)
            digitalWrite(leds[i], HIGH);

        if (grupo == 1) {
            angulo1 += incremento1;
            if (angulo1 >= 180 || angulo1 <= 0) {
                incremento1 = -incremento1;
                grupo = 2;
            }
            for (int i = 0; i < 3; i++)
                servosGrupo1[i].write(angulo1);
        } else {
            angulo2 += incremento2;
            if (angulo2 >= 180 || angulo2 <= 0) {
                incremento2 = -incremento2;
                grupo = 1;
            }
            for (int i = 0; i < 3; i++)
                servosGrupo2[i].write(angulo2);
        }

        delay(20); // tempo de espera entre cada atualização dos servos
    } else {
        // apaga todos os LEDs
        for (int i = 0; i < numLeds; i++)
            digitalWrite(leds[i], LOW);
    }
}