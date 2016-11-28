/**********************************************
*         Arquivo: CarrinhoServo.cpp          *
*   Implementacao da classe CarrinhoServo     *
**********************************************/

#include<Arduino.h>
#include<CarrinhoServo.h>

/************************************************************
*               Metodo construtor do carrinho.              *
*   Abstrai todas as configuracoes e dspositivos conectados *
*   ao carrinho.                                            *
*************************************************************/
CarrinhoServo::CarrinhoServo(ServoMotor *servoDireito,
                             ServoMotor *servoEsquerdo,
                             Ultrasonic *frontal,
                             Ultrasonic *lateral)
  :direito(servoDireito),
  esquerdo(servoEsquerdo),
  frontal(frontal),
  lateral(lateral) {}


void CarrinhoServo::config()
/************************************************************
*                                                           *
* Configura todos os dispositivos conectados ao carrinho.   *
*                                                           *
************************************************************/
{
  frontal->Config();
  lateral->Config();

  direito->s->attach(direito->porta);
  direito->s->write(direito->angulo);

  esquerdo->s->attach(esquerdo->porta);
  esquerdo->s->write(esquerdo->angulo);
}
int CarrinhoServo::analisar()
/*********************************************************************
* Funcao de analise de distancias                                    *
* *Retorna 1 quando o sensor lateral nao detecta um objeto a         *
* *pelo menos 17 cm de distancia.                                    *
*                                                                    *
* *Retorna 2 quando os sensores frontal e lateral nao detectam       *
* *um objeto a pelo menos 16 e 25 cm respectivamente.                *
*                                                                    *
* *Retorna 3 quando o sensor frontal detecta um objeto a pelo        *
* *menos 16 cm e o sensor lateral nao detecta um objeto a esquerda   *
* *a pelo menos 25cm de distancia.                                   *
*                                                                    *
* *Retorna 0 quando nenhuma das opcoes foi verificada.               *
*********************************************************************/

{
  if(this->livreAEsquerda())
    return 1;
  if(!this->livreAEsquerda() && !this->livreAFrente())
    return 2;
  if(this->livreAFrente() && !this->livreAEsquerda())
    return 3;
  return 0;
}

long CarrinhoServo::getDistanciaFrontal()
/*******************************************************************
* Chama a funcao do sensor frontal para obter a distancia nenhuma  *
* num determinado instante.                                        *
*******************************************************************/
{return frontal->Ranging(CM);}

long CarrinhoServo::getDistanciaLateral()
/*******************************************************************
* Chama a funcao do sensor lateral para obter a distancia nenhuma  *
* num determinado instante.                                        *
*******************************************************************/
{return lateral->Ranging(CM);}

bool CarrinhoServo::livreAFrente()
/******************************************************************
*                                                                 *
*     Faz a leitura da distancia do carrinho a um objeto num      *
*     determinado instante, usando o sensor frontal.                                       *
*                                                                 *
******************************************************************/
{return (getDistanciaFrontal() > 16);}

bool CarrinhoServo::livreAEsquerda()
/******************************************************************
*                                                                 *
*     Faz a leitura da distancia do carrinho a um objeto num      *
*     determinado instante, usando o sensor lateral.              *                         *
*                                                                 *
******************************************************************/
{return (getDistanciaLateral() > 25);}

void CarrinhoServo::ajustar()
/******************************************************************
* Devido a um problema detectado ao ligar o carrinho              *
* que o faz virar um pouco a esquerda, surgia a necessidade de    *
* criar uma funcao que corrigisse esse problema.                  *
* Esta funcao ajusta a posicao do carrinho ao liga-lo.            *
******************************************************************/
{
  direito->s->write(28 - direito->angulo);
  esquerdo->s->write(20 - esquerdo->angulo);
  delay(170);
  this->parar();
}

void CarrinhoServo::meiaVolta()
/******************************************************************
*                   Faz o carrinho virar 180 graus.               *
******************************************************************/
{
  direito->s->write(20 - direito->angulo);
  esquerdo->s->write(20 - esquerdo->angulo);
  delay(1000);
  this->parar();
}

void CarrinhoServo::esquerda()
/******************************************************************
*                   Faz o carrinho virar para a esquerda.         *
******************************************************************/
{
  direito->s->write(direito->angulo + 28);
  esquerdo->s->write(esquerdo->angulo);
  delay(1000);
  this->parar();
}

void CarrinhoServo::direita()
/******************************************************************
*                   Faz o carrinho virar para a direita.         *
******************************************************************/
{
  direito->s->write(28 - direito->angulo);
  esquerdo->s->write(20 - esquerdo->angulo);
  delay(520);
  this->parar();
}

void CarrinhoServo::passo()
/******************************************************************
*       Faz o carrinho dar um passo de aproximadamente 12cm.      *
******************************************************************/
{
  direito->s->write(97 + direito->angulo);
  esquerdo->s->write(85.5 - esquerdo->angulo);
  delay(800);
}

void CarrinhoServo::meioPasso()
/******************************************************************
*       Faz o carrinho dar um passo de aproximadamente 8cm.      *
******************************************************************/
{
  direito->s->write(97 + direito->angulo);
  esquerdo->s->write(85.5 - esquerdo->angulo);
  delay(500);
}

void CarrinhoServo::parar()
/******************************************************************
*                   Faz o carrinho parar                          *
******************************************************************/
{
  direito->s->write(direito->angulo);
  esquerdo->s->write(esquerdo->angulo);
  delay(1000);
}
