/**********************************************
*                                             *
*         Arquivo: CarrinhoServo.h            *
*                                             *
**********************************************/
#ifndef CARRINHO_SERVO_H
#define CARRINHO_SERVO_H

#include<Servo.h>
#include<Ultrasonic.h>

typedef struct ServoMotor_
/******************************************************************
*     Struct que abstrai insformacoes necessarias para            *
*               o funcionamento do ServoMotor                     *
*                                                                 *
*     Atributos: 1 ponteiro para o servo.                         *
*                1 inteiro que guarda o valor do angulo do servo. *
*                1 inteiro que guarda a porta do servo.           *
*                                                                 *
******************************************************************/
{
  Servo *s;
  int angulo, porta;
  ServoMotor_(Servo *ser, int ang, int port)
  :s(ser), angulo(ang), porta(port){};
} ServoMotor;

class CarrinhoServo
/*****************************************************************
*                                                                *
*       Classe: CarrinhoServo                                    *
*       Feita para simular um carrinho com dois motores servo    *
*       e dois sensores ligados em um Arduino Uno.               *
*                                                                *
*****************************************************************/
{
public:
  //Metodo contrutor.
  CarrinhoServo(ServoMotor*, ServoMotor*, Ultrasonic*, Ultrasonic*);

  //Metodo de configuracao.
  void config();

  //Analise do ambiente.
  int analisar();
  bool livreAFrente();
  bool livreAEsquerda();
  long getDistanciaFrontal();
  long getDistanciaLateral();

  //Movimentos.
  void ajustar();
  void meiaVolta();
  void esquerda();
  void direita();
  void passo();
  void meioPasso();
  void parar();
private:
  Ultrasonic *frontal, *lateral;
  ServoMotor *direito, *esquerdo;
};

#endif
