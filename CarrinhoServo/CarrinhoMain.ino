#include <CarrinhoServo.h>
#include <Servo.h>
#include <Ultrasonic.h>

//Configuracoes do sensor frontal.
#define FrontalTriggerPin  7
#define FrontalEchoPin     6
//Configuracoes do sensor frontal.
#define LateralTriggerPin  13
#define LateralEchoPin 12

//configuracoes do ServoMotor Direito
#define anguloD 85
#define portaD 9
//configuracoes do ServoMotor Esquerdo
#define anguloE 89
#define portaE 8


CarrinhoServo *carrinho = new CarrinhoServo(new ServoMotor(new Servo(), anguloD, portaD),
                                            new ServoMotor(new Servo(), anguloE, portaE),
                                            new Ultrasonic(FrontalTriggerPin, FrontalEchoPin),
                                            new Ultrasonic(LateralTriggerPin, LateralEchoPin));

int count = 0;
void setup() {
  carrinho->config();
  Serial.begin(9600);
}

void loop() {
  if(count == 0) {
    carrinho->ajustar();
    count++;
  }
  switch(carrinho->analisar()) {
    case 1:
      if(carrinho->livreAFrente()) carrinho->meioPasso();
      carrinho->esquerda();
      carrinho->passo();
      carrinho->parar();
      break;
    case 2:
      carrinho->direita();
      carrinho->parar();
      break;
    case 3:
      carrinho->passo();
      break;
    default:
      carrinho->parar();
    break;
  }
  delay(200);
}
