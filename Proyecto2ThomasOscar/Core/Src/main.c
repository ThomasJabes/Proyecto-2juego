/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9341.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
extern uint8_t fondo[];
extern uint8_t menu[];
extern uint8_t selecion[];
extern uint8_t flecha[];
extern uint8_t perro[];
extern uint8_t perro1[];
extern uint8_t perro2[];
extern uint8_t perro3[];
extern uint8_t perro4[];
extern uint8_t perro5[];
extern uint8_t perro6[];
extern uint8_t perro7[];
extern uint8_t Ronda[];
extern uint8_t Patos[];
extern uint8_t mira1[];
extern uint8_t Caza[];
extern uint8_t patocayendo[];
extern uint8_t muerto[];
extern uint8_t Rojo[];
extern uint8_t patox[];
extern uint8_t mira2[];

//variables
int menu_position = 0;  // Posición del menú
int coorX = 100;  // Posición inicial X del pato
int coorY = 60;   // Posición inicial Y del pato
int patoWidth = 29;  // Ancho del sprite del pato
int patoHeight = 31; // Alto del sprite del pato
int velocidadX = 1;  // Velocidad en el eje X
int velocidadY = 1;  // Velocidad en el eje Y
int limiteSuperior = 0, limiteInferior = 140, limiteIzquierdo = 0, limiteDerecho = 320;  // Límites del área azul
int animFrame = 0;  // Frame inicial de animación del pato
int direccionDerecha = 1;  // Dirección del pato
int miraX = 160;  // Posición inicial X de la mira
int miraY = 120;  // Posición inicial Y de la mir
int lastMiraX = 160;  // Posición inicial X de la mira
int lastMiraY = 120;  // Posición inicial Y de la mira
int patoMuerto = 0;  // Indica si el pato ha sido disparado
int patoCayendo = 0; // Indica si el pato está en proceso de caer
int miraDisparo = 0; // Indica si se ha presionado el botón para disparar
int coorXPatoMuerto, coorYPatoMuerto; // Coordenadas del pato muerto
int contadorvidasP = 0;  // Contador de vidas de los patos
int posicionesX[6] = {50, 120, 200, 60, 150, 180};  // Posiciones X predefinidas
int posicionesY[6] = {40, 60, 80, 100, 50, 90};     // Posiciones Y predefinidas
int vidaActual = 0;  // Variable para controlar cuántas vidas (patos) quedan

int coorX2 = 150;  // Posición inicial X del segundo pato
int coorY2 = 80;   // Posición inicial Y del segundo pato
int pato2Muerto = 0;  // Indica si el segundo pato ha sido disparado
int pato2Cayendo = 0; // Indica si el segundo pato está en proceso de caer
int coorXPato2Muerto, coorYPato2Muerto; // Coordenadas del segundo pato muerto

int numeroPatos = 1;  // Número de patos, por defecto es 1, pero cambia a 2 en la segunda opción del menú
int decoracionFrame = 0;

int miraX2 = 160;  // Posición inicial X de la mira del segundo jugador
int miraY2 = 120;  // Posición inicial Y de la mira del segundo jugador
int lastMiraX2 = 160;  // Última posición X de la mira del segundo jugador
int lastMiraY2 = 120;  // Última posición Y de la mira del segundo jugador
int miraDisparo2 = 0;  // Indica si se ha presionado el botón del segundo jugador
int lastMira2X = 160;  // Posición inicial X de la segunda mira
int lastMira2Y = 120;  // Posición inicial Y de la segunda mira
int mira2X = 160;  // Posición inicial X de la segunda mira
int mira2Y = 120;  // Posición inicial Y de la segunda mira



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* Función para leer valores del ADC */
int Read_ADC(uint32_t channel) {
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    int value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

    return value;
}

/* Función para iniciar el juego */
void startGame() {
		contadorvidasP = 0;
    // Dibuja el fondo completo inicialmente
		LCD_Bitmap(0, 0, 320, 240, fondo);
		LCD_Bitmap(105, 143, 54, 46, perro1);  // Dibuja el primer frame del perro
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	// Desplaza ligeramente el perro y cambia la imagen
    	LCD_Bitmap(109, 147, 57, 42, perro2);  // Dibuja el segundo frame
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	// Continúa desplazando el perro
    	LCD_Bitmap(113, 147, 57, 42, perro3);  // Dibuja el tercer frame
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	LCD_Bitmap(117, 147, 57, 42, perro2);  // Dibuja el cuarto frame
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	LCD_Bitmap(121, 147, 57, 42, perro3);  // Dibuja el quinto frame
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	LCD_Bitmap(125, 147, 57, 42, perro2);  // Dibuja el sexto frame
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	LCD_Bitmap(129, 147, 57, 42, perro3);  // Dibuja el séptimo frame
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	// Salto del perro
    	LCD_Bitmap(132, 142, 57, 53, perro4);  // Dibuja el perro saltando
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	LCD_Bitmap(136, 122, 37, 48, perro5);  // Dibuja el siguiente frame del salto
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	LCD_Bitmap(150, 114, 37, 48, perro6);  // Dibuja el siguiente frame del salto
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo

    	LCD_Bitmap(175, 132, 33, 33, perro7);  // Dibuja el perro aterrizando
    	HAL_Delay(5);
    	LCD_Bitmap(0, 0, 320, 240, fondo);  // Redibuja el fondo completo
    	HAL_Delay(1000);  // Pausa antes de mostrar la ronda

    	FillRect(0, 0, 100, 40,  0x559D);  // Rellena la pantalla con color celeste
    	LCD_Print("    Estas Listo!", 20, 80, 2, 0x0000,  0x559D);  // Texto negro con fondo celeste
    	HAL_Delay(1000);
    	LCD_Bitmap(0, 0, 320, 240, fondo);
    	FillRect(0, 0, 100, 40, 0x559D);  // �?rea donde aparece el número
    	LCD_Print("3", 150, 80, 2, 0x0000, 0x559D);  // Texto negro
    	HAL_Delay(1000);  // Pausa de 1 segundo
    	LCD_Bitmap(0, 0, 320, 240, fondo);
    		    // Muestra el número "2" con fondo celeste
    	FillRect(0, 0, 100, 40, 0x559D);  // �?rea donde aparece el número
    	LCD_Print("2", 150, 80, 2, 0x0000, 0x559D);  // Texto negro
    	HAL_Delay(1000);  // Pausa de 1 segundo
    	LCD_Bitmap(0, 0, 320, 240, fondo);
    		    // Muestra el número "1" con fondo celeste
    	FillRect(0, 0, 100, 40, 0x559D);  // �?rea donde aparece el número
    	LCD_Print("1", 150, 80, 2, 0x0000, 0x559D);  // Texto negro
    	HAL_Delay(1000);  // Pausa de 1 segundo
    		// Dibuja los indicadores de ronda
    	LCD_Bitmap(0, 0, 320, 240, fondo);

    	LCD_Bitmap(120, 220, 9, 9, Ronda);
    	LCD_Bitmap(132, 220, 9, 9, Ronda);
    	LCD_Bitmap(144, 220, 9, 9, Ronda);
    	LCD_Bitmap(156, 220, 9, 9, Ronda);
    	LCD_Bitmap(168, 220, 9, 9, Ronda);
    	LCD_Bitmap(180, 220, 9, 9, Ronda);

    // Continuar con el resto de la animación
}

/* Función para dibujar el menú */
void drawMenu(){
    LCD_Clear(0x00);  // Limpia la pantalla
    LCD_Bitmap(50, 0, 250, 216, selecion);  // Dibuja el menú de selección

    // Mostrar el sprite decorativo del pato en el menú (a la izquierda)
    animarDecoracion();  // Llama a la función para animar el pato decorativo

    // Mostrar las opciones del menú
    if (menu_position == 0) {
        LCD_Bitmap(100, 125, 11, 7, flecha);  // Flecha en la primera opción
    } else {
        LCD_Bitmap(100, 140, 11, 7, flecha);  // Flecha en la segunda opción
    }
}
void animarDecoracion() {
    // Alternar entre los dos frames de animación del pato decorativo
    decoracionFrame = (decoracionFrame + 1) % 2;  // 2 frames para la animación de 'patox'

    // Dibuja el sprite decorativo a la izquierda del menú (posición X: 10, Y: 100)
    LCD_Sprite(50, 125, 45, 40, patox, 2, decoracionFrame, 0, 1);

    // Control de velocidad de animación (ajustable)
    HAL_Delay(200);  // Controla la velocidad de cambio entre los dos frames
}
/* Función para manejar el menú */
/* Función para manejar el menú */
void menuSelection() {
    LCD_Bitmap(50, 0, 250, 216, selecion);
    LCD_Bitmap(100, 125, 11, 7, flecha);
    LCD_Bitmap(100, 140, 11, 7, flecha);

    while (1) {
        int xValue1, yValue1, buttonState1;
        int xValue2, yValue2, buttonState2;

        // Leer valores de joystick 1 (jugador 1)
        xValue1 = Read_ADC(ADC_CHANNEL_9);  // Eje X en PB1 (canal ADC 9)
        yValue1 = Read_ADC(ADC_CHANNEL_12);  // Eje Y en PC2 (canal ADC 12)
        buttonState1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);  // Leer estado del botón en PB13

        // Leer valores de joystick 2 (jugador 2)
        xValue2 = Read_ADC(ADC_CHANNEL_14);  // Eje X del segundo joystick en PC4 (canal ADC 14)
        yValue2 = Read_ADC(ADC_CHANNEL_15);  // Eje Y del segundo joystick en PC5 (canal ADC 15)
        buttonState2 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);  // Leer estado del botón en PB15

        // Mover flecha según el valor de Y de cualquiera de los dos joysticks
        if ((yValue1 < 1000 || yValue2 < 1000) && menu_position > 0) {
            menu_position = 0;
            drawMenu();  // Redibuja el menú
        } else if ((yValue1 > 3000 || yValue2 > 3000) && menu_position < 1) {
            menu_position = 1;
            drawMenu();  // Redibuja el menú
        }

        // Si cualquiera de los botones se presiona, selecciona la opción
        if (buttonState1 == 0 || buttonState2 == 0) {
            if (menu_position == 0) {
                numeroPatos = 1;  // Configura para un solo pato
                startGame();  // Inicia el juego con un pato
                break;
            } else if (menu_position == 1) {
                numeroPatos = 2;  // Configura para dos patos
                startGame();  // Inicia el juego con dos patos
                break;
            }
        }

        HAL_Delay(200);  // Retardo para evitar rebotes
    }
}

void matarPato(int miraX1, int miraY1, int miraX2, int miraY2) {
    // Detectar si la mira del jugador 1 está sobre el pato y se presionó su botón
    if ((miraX1 > coorX && miraX1 < coorX + patoWidth && miraY1 > coorY && miraY1 < coorY + patoHeight) &&
        HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET && !patoMuerto) {

        patoMuerto = 1;  // Indica que el pato ha sido disparado
        patoCayendo = 1; // Empieza el proceso de caída
        coorXPatoMuerto = coorX; // Guarda la posición donde murió el pato
        coorYPatoMuerto = coorY;

        // Dibuja el pato muerto en la posición donde fue disparado
        LCD_Sprite(coorXPatoMuerto, coorYPatoMuerto, 32, 32, muerto, 1, 0, 0, 1);
        HAL_Delay(500);  // Pausa breve antes de que el pato empiece a caer
    }
    // Detectar si la mira del jugador 2 está sobre el pato y se presionó su botón
    else if ((miraX2 > coorX && miraX2 < coorX + patoWidth && miraY2 > coorY && miraY2 < coorY + patoHeight) &&
             HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_RESET && !patoMuerto) {

        patoMuerto = 1;  // Indica que el pato ha sido disparado
        patoCayendo = 1; // Empieza el proceso de caída
        coorXPatoMuerto = coorX; // Guarda la posición donde murió el pato
        coorYPatoMuerto = coorY;

        // Dibuja el pato muerto en la posición donde fue disparado
        LCD_Sprite(coorXPatoMuerto, coorYPatoMuerto, 32, 32, muerto, 1, 0, 0, 1);
        HAL_Delay(500);  // Pausa breve antes de que el pato empiece a caer
    }
}


void patorojo() {
    if (contadorvidasP >= 1) {
        LCD_Bitmap(120, 220, 9, 9, Rojo);  // Primer pato eliminado
    }
    if (contadorvidasP >= 2) {
        LCD_Bitmap(132, 220, 9, 9, Rojo);  // Segundo pato eliminado
    }
    if (contadorvidasP >= 3) {
        LCD_Bitmap(144, 220, 9, 9, Rojo);  // Tercer pato eliminado
    }
    if (contadorvidasP >= 4) {
        LCD_Bitmap(156, 220, 9, 9, Rojo);  // Cuarto pato eliminado
    }
    if (contadorvidasP >= 5) {
        LCD_Bitmap(168, 220, 9, 9, Rojo);  // Quinto pato eliminado
    }
    if (contadorvidasP >= 6) {
        LCD_Bitmap(180, 220, 9, 9, Rojo);  // Sexto pato eliminado
    }
}

void caerPato() {
    if (patoCayendo) {
        int limiteGrama = 120; // Ajusta este valor para que coincida con la altura de la grama

        while (coorYPatoMuerto < limiteGrama) {
            // Borra la posición anterior del pato muerto redibujando el fondo en esa área
            LCD_Bitmap(coorXPatoMuerto, coorYPatoMuerto, 32, 32, fondo);

            // Mueve el pato hacia abajo
            coorYPatoMuerto += 3;  // Velocidad de caída del pato

            // Dibuja el pato cayendo
            animFrame = (animFrame + 1) % 3;
            LCD_Sprite(coorXPatoMuerto, coorYPatoMuerto, 32, 32, patocayendo, 3, animFrame, 0, 1);

            HAL_Delay(50);  // Pausa para controlar la velocidad de la caída
        }

        // Cuando el pato llega al límite de la grama, se muestra el perro levantando el pato
        HAL_Delay(500);  // Pausa breve antes de mostrar el perro
        LCD_Bitmap(coorXPatoMuerto, coorYPatoMuerto, 32, 32, fondo); // Borra el pato caído

        // Ajustamos la posición del perro para que esté justo en la grama
        LCD_Sprite(coorXPatoMuerto - 10, limiteGrama, 46, 38, Caza, 1, 0, 0, 1); // Ajustar la posición Y para que el perro esté justo en la grama

        HAL_Delay(1000);  // Pausa para mostrar la animación del perro

        // Borra la imagen del perro después de la animación
        LCD_Bitmap(coorXPatoMuerto - 10, limiteGrama, 46, 38, fondo);

        // Incrementa el contador de vidas y muestra los patos eliminados
        contadorvidasP++;
        patorojo();  // Llama a la función para mostrar las vidas

        // Verifica si se han eliminado 6 patos
        if (contadorvidasP >= 6) {
            // Mostrar mensaje de "Juego Terminado"
            LCD_Clear(0x00);  // Limpia la pantalla
            LCD_Print("Juego Terminado", 50, 100, 2, 0xFFFF, 0x0000);  // Muestra el mensaje
            HAL_Delay(3000);  // Pausa de 3 segundos para que se vea el mensaje

            // Opcional: Reiniciar el juego
            contadorvidasP = 0;  // Reinicia el contador de patos eliminados
            menuSelection();     // Vuelve al menú principal para reiniciar el juego
            return;  // Salir de la función para no continuar
        }

        // Reinicia la animación del pato volando si no se ha llegado al límite de 6 patos
        patoMuerto = 0;
        patoCayendo = 0;
        coorX = 100;  // Reinicia la posición del pato
        coorY = 60;   // Reinicia la posición del pato
    }
}




/* Función para mover el pato */
void moverPato() {
    // Mover el primer pato
    if (!patoMuerto) {
        // Borra la posición anterior del primer pato redibujando el fondo en esa área
        LCD_Bitmap(coorX, coorY, patoWidth, patoHeight, fondo);

        // Actualiza las coordenadas del primer pato para moverlo
        coorX += velocidadX;
        coorY += velocidadY;

        // Control de límites en el área azul para el primer pato
        if (coorX >= limiteDerecho - patoWidth || coorX <= limiteIzquierdo) {
            velocidadX = -velocidadX;  // Cambia la dirección en X
            direccionDerecha = !direccionDerecha;  // Cambia la dirección visual del pato
        }

        if (coorY >= limiteInferior - patoHeight || coorY <= limiteSuperior) {
            velocidadY = -velocidadY;  // Cambia la dirección en Y
        }

        // Actualiza el frame de la animación de aleteo del primer pato (0, 1, 2)
        animFrame = (animFrame + 1) % 3;

        // Dibuja el sprite del primer pato en la nueva posición y frame de animación
        LCD_Sprite(coorX, coorY, patoWidth, patoHeight, Patos, 3, animFrame, direccionDerecha, 1);

        // Detecta si alguno de los jugadores ha disparado al pato
        matarPato(miraX, miraY, mira2X, mira2Y);  // Pasar las coordenadas de las dos miras al mismo tiempo
    } else if (patoCayendo) {
        caerPato();  // Hacer caer el primer pato
    }

    // Si la opción es de dos patos, también mueve el segundo pato
    if (numeroPatos == 2) {
        if (!pato2Muerto) {
            // Borra la posición anterior del segundo pato redibujando el fondo en esa área
            LCD_Bitmap(coorX2, coorY2, patoWidth, patoHeight, fondo);

            // Actualiza las coordenadas del segundo pato para moverlo
            coorX2 += velocidadX;
            coorY2 += velocidadY;

            // Control de límites en el área azul para el segundo pato
            if (coorX2 >= limiteDerecho - patoWidth || coorX2 <= limiteIzquierdo) {
                velocidadX = -velocidadX;
                direccionDerecha = !direccionDerecha;
            }

            if (coorY2 >= limiteInferior - patoHeight || coorY2 <= limiteSuperior) {
                velocidadY = -velocidadY;
            }

            // Actualiza el frame de la animación de aleteo del segundo pato (0, 1, 2)
            animFrame = (animFrame + 1) % 3;

            // Dibuja el sprite del segundo pato en la nueva posición y frame de animación
            LCD_Sprite(coorX2, coorY2, patoWidth, patoHeight, Patos, 3, animFrame, direccionDerecha, 1);

            // Detecta si alguno de los jugadores ha disparado al segundo pato
            matarPato(miraX, miraY, mira2X, mira2Y);  // Pasar las coordenadas de las dos miras al mismo tiempo
        } else if (pato2Cayendo) {
            caerPato2();  // Hacer caer el segundo pato
        }
    }

    HAL_Delay(50);  // Control de velocidad del movimiento del pato
}



void matarPato2(int miraX, int miraY) {
    if ((miraX > coorX2 && miraX < coorX2 + patoWidth) && (miraY > coorY2 && miraY < coorY2 + patoHeight) && HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET && !pato2Muerto) {
        pato2Muerto = 1;
        pato2Cayendo = 1;
        coorXPato2Muerto = coorX2;
        coorYPato2Muerto = coorY2;

        LCD_Sprite(coorXPato2Muerto, coorYPato2Muerto, 32, 32, muerto, 1, 0, 0, 1);
        HAL_Delay(500);
    }
}
void caerPato2() {
    if (pato2Cayendo) {
        int limiteGrama = 120;

        while (coorYPato2Muerto < limiteGrama) {
            LCD_Bitmap(coorXPato2Muerto, coorYPato2Muerto, 32, 32, fondo);
            coorYPato2Muerto += 3;

            animFrame = (animFrame + 1) % 3;
            LCD_Sprite(coorXPato2Muerto, coorYPato2Muerto, 32, 32, patocayendo, 3, animFrame, 0, 1);
            HAL_Delay(50);
        }

        HAL_Delay(500);
        LCD_Bitmap(coorXPato2Muerto, coorYPato2Muerto, 32, 32, fondo);
        LCD_Sprite(coorXPato2Muerto - 10, limiteGrama, 46, 38, Caza, 1, 0, 0, 1);

        HAL_Delay(1000);
        LCD_Bitmap(coorXPato2Muerto - 10, limiteGrama, 46, 38, fondo);

        contadorvidasP++;
        patorojo();

        pato2Muerto = 0;
        pato2Cayendo = 0;
        coorX2 = 150;
        coorY2 = 80;
    }
}


void moverMira() {
    // Leer valores del joystick del primer jugador (mira1)
    int xValue1 = Read_ADC(ADC_CHANNEL_9);  // Leer el valor X del joystick 1
    int yValue1 = Read_ADC(ADC_CHANNEL_12);  // Leer el valor Y del joystick 1

    // Actualiza la posición de la mira del primer jugador
    miraX += (xValue1 - 2048) / 100;
    miraY += (yValue1 - 2048) / 100;

    // Limita la posición de la mira dentro del área permitida (jugador 1)
    if (miraX < limiteIzquierdo) miraX = limiteIzquierdo;
    if (miraX > limiteDerecho - 26) miraX = limiteDerecho - 26;  // 26 es el ancho de la mira
    if (miraY < limiteSuperior) miraY = limiteSuperior;
    if (miraY > limiteInferior - 23) miraY = limiteInferior - 23;  // 23 es el alto de la mira

    // Limpiar la posición anterior de la mira del jugador 1 redibujando el fondo en esa área
    LCD_Bitmap(lastMiraX, lastMiraY, 26, 23, fondo);

    // Dibuja la mira del jugador 1 en su nueva posición
    LCD_Sprite(miraX, miraY, 26, 23, mira1, 1, 0, 0, 1);

    // Actualiza la posición anterior de la mira del jugador 1
    lastMiraX = miraX;
    lastMiraY = miraY;

    // Leer valores del joystick del segundo jugador (mira2)
    int xValue2 = Read_ADC(ADC_CHANNEL_14);  // Leer el valor X del joystick 2 (canal 14)
    int yValue2 = Read_ADC(ADC_CHANNEL_15);  // Leer el valor Y del joystick 2 (canal 15)

    // Actualiza la posición de la mira del segundo jugador
    mira2X += (xValue2 - 2048) / 100;
    mira2Y += (yValue2 - 2048) / 100;

    // Limita la posición de la mira dentro del área permitida (jugador 2)
    if (mira2X < limiteIzquierdo) mira2X = limiteIzquierdo;
    if (mira2X > limiteDerecho - 26) mira2X = limiteDerecho - 26;  // 26 es el ancho de la mira
    if (mira2Y < limiteSuperior) mira2Y = limiteSuperior;
    if (mira2Y > limiteInferior - 23) mira2Y = limiteInferior - 23;  // 23 es el alto de la mira

    // Limpiar la posición anterior de la mira del jugador 2 redibujando el fondo en esa área
    LCD_Bitmap(lastMira2X, lastMira2Y, 26, 23, fondo);

    // Dibuja la mira del jugador 2 en su nueva posición
    LCD_Sprite(mira2X, mira2Y, 26, 23, mira2, 1, 0, 0, 1);

    // Actualiza la posición anterior de la mira del jugador 2
    lastMira2X = mira2X;
    lastMira2Y = mira2Y;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  FillRect(0, 0, 320, 240, 0x00);
  LCD_Bitmap(0, 0, 277, 270, menu);  // Menú del juego
  HAL_Delay(2000);
  LCD_Clear(0x00);

  menuSelection();  // Llama a la función para manejar el menú
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    moverPato();  // Llamar a la función para mover el pato
    moverMira();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LCD_RST_Pin|LCD_D1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin|LCD_D7_Pin
                          |LCD_D0_Pin|LCD_D2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin|LCD_D6_Pin|LCD_D3_Pin|LCD_D5_Pin
                          |LCD_D4_Pin|SD_SS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LCD_RST_Pin LCD_D1_Pin */
  GPIO_InitStruct.Pin = LCD_RST_Pin|LCD_D1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RD_Pin LCD_WR_Pin LCD_RS_Pin LCD_D7_Pin
                           LCD_D0_Pin LCD_D2_Pin */
  GPIO_InitStruct.Pin = LCD_RD_Pin|LCD_WR_Pin|LCD_RS_Pin|LCD_D7_Pin
                          |LCD_D0_Pin|LCD_D2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_CS_Pin LCD_D6_Pin LCD_D3_Pin LCD_D5_Pin
                           LCD_D4_Pin SD_SS_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin|LCD_D6_Pin|LCD_D3_Pin|LCD_D5_Pin
                          |LCD_D4_Pin|SD_SS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
