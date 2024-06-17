# Modelismo de carro elétrico para captação de Dados
### Contexto
O Challenge é um desafio apresentado aos alunos da FIAP todos os anos. Neste ano, o desafio para os estudantes do primeiro ano de Engenharia de Software foi a popularização da Fórmula E, trazida pela empresa Tech Mahindra. Para nossa solução, é necessário desenvolver um modelo de um carro elétrico para simular um carro real, a fim de realizar testes com a captação de dados dos sensores treinados por nós, envolvendo nossa solução.

Integrantes do Grupo:

Nome   | RM
--------- | ------
Arthur Abonizio | 555506 
Enzo Dias | 558225
Gustavo Henrique | 556712
Milena Garcia | 555111
Steffany Medeiros | 556262

### Descrição do Projeto
Nossa solução, resumidamente, é um Ecossistema Digital que permite aos usuários maior interação com as corridas, tornando-as mais divertidas e dinâmicas. Um dos fatores principais é relatar em nossa plataforma dados dos carros da corrida em tempo real, como velocidade, temperatura do motor e carga da bateria, além de outras inúmeras possibilidades que desejarmos. Para confirmar se o sistema criado está funcionando corretamente, precisamos testá-lo. Por isso, precisamos criar um modelo de carro para realizar os testes, ou seja, um carrinho de controle remoto.

### Requisitos e Funcionalidade
Os materiais necessários para fazer o modelo são:
* 2 Microprocessadores (um para o carro modelo e outro para o controle);
* 1 Chassi;
* 2 rodas traseiras e uma roda universal ou 4 rodas, porém com motor servo para direção das rodas frontais;
* 2 motores DC (corrente contínua);
* 1 Módulo Ponte H dupla para motores DC;
* 4 pilhas AA (necessário case de pilhas para seu funcionamento);
* 2 Power bank / baterias de 9v (um para o modelo e outro para o controle);
* 2 Módulos de radio frequência (um emissor e outro receptor);
* 2 Cabos USB;
* 1 joystick;
* Conexão a internet para o envio de dados (ESP32 como ótima opção);
* Cabos conforme necessário;
* Sensores para teste conforme necessário;

### Objetivos
O objetivo do projeto é criar um modelo para a execução de testes práticos no envio de informações dos carros, como velocidade, temperatura do motor e carga da bateria, para nossa plataforma digital, a fim de promover uma maior dinâmica e interação com o usuário durante a corrida.

### Observações
Atualmente no projeto está sendo realizado testes com a captação de dados de velocidade do motor via sensores de pulsos.

![Esquematização da simulação da ponte H no tinkercad](https://github.com/guta231/modelismo-carro-eletrico/blob/main/imagem%20esquematizada%20tinkercad.png)

Clique [aqui](https://www.tinkercad.com/things/435US7UQ3Br-simulcao-de-funcionamento-de-controle-de-motores-com-ponte-h/editel) para ver a simulação do funcionamento de uma ponte H no tinkercad.
