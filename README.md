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

### Objetivos
O objetivo do projeto é criar um modelo para a execução de testes práticos no envio de informações dos carros, como velocidade, temperatura do motor e carga da bateria para nossa plataforma digital com a finalidade de promover dinâmica e interação com o usuário durante a corrida.


### Requisitos e Funcionalidade
Os materiais necessários para fazer o modelo são:
* 1 ESP32;
* 1 Arduino UNO;
* 1 Módulo bluetooth (HC-05);
* 1 Chassi;
* 2 rodas traseiras e uma roda universal ou 4 rodas, porém com motor servo para direção das rodas frontais;
* 2 motores DC (corrente contínua);
* 1 Módulo Ponte H dupla para motores DC;
* 4 pilhas AA (necessário case de pilhas para seu funcionamento);
* 1 Power bank / baterias de 9v;
* 2 Cabos USB;
* Conexão ao WiFi para o envio de dados;
* Cabos conforme necessário;
* Sensores para teste conforme necessário;
* Servidor com container Broker MQTT;

### Passos para configuração do servidor

1. * Criar Maquina virtual Linux Ubuntu usando Azure ou qualquer outro serviço e abra um terminal

2. **Conecte ao servidor via SSH após liga-lo**

    ```bash
    ssh <nome-do-usuario>@<IP_da_VM>
    ```

2. **Instale dependências**

    ```bash
    sudo apt update
    ```
    ```bash
    sudo apt-get install net-tools
    ```
    *Instale o Git;

    ```bash
    sudo apt install git
    ```

3. **Instale o Docker**

    ```bash
    sudo apt install apt-transport-https ca-certificates curl software-properties-common -y
    ```

    ```bash
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
    ```

    ```bash
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
    ```

    ```bash
    sudo apt update
    ```

    ```bash
    sudo apt install docker-ce docker-ce-cli containerd.io -y
    ```

4. **Verifique se o Docker está funcionando**

    ```bash
    sudo systemctl status docker
    ```

5. **Clone o repositório do fiware descomplicado**

    ```bash
    git clone https://github.com/fabiocabrini/fiware
    ```

6. **Entre na pasta e inicie os containers**

    ```bash
    cd fiware
    ```

    ```bash
    sudo docker compose up -d
    ```

    * Verifique se está funcionando corretamente

    ```bash
    sudo docker stats
    ```

7. **Instale o node-red para tratar os dados**

   ```bash
   sudo npm install -g --unsafe-perm node-red
   ```

   * Inicializar node-red

   ```bash
   node-red
   ```

8. **Crie o container MySQL**

   ```bash
   sudo docker run --name mysql-container -e MYSQL_ROOT_PASSWORD=sua_senha_root -e MYSQL_DATABASE=seu_banco_de_dados -e MYSQL_USER=seu_usuario -e MYSQL_PASSWORD=sua_senha -p 3306:3306 -d mysql:latest
   ````

   Legenda:
* --name mysql-container: Nome do container.
* -e MYSQL_ROOT_PASSWORD=sua_senha_root: Define a senha do usuário root do MySQL.
* -e MYSQL_DATABASE=seu_banco_de_dados: Cria um banco de dados inicial.
* -e MYSQL_USER=seu_usuario: Define um usuário adicional.
* -e MYSQL_PASSWORD=sua_senha: Define a senha para o usuário adicional.
* -p 3306:3306: Mapeia a porta 3306 do container para a porta 3306 do host.
* -d mysql:latest: Usa a imagem mais recente do MySQL e executa o container em segundo plano.

9. **De permissão ao acesso das portas**

* 1883: Broker MQTT
* 3306: MySQL
* 1880: node-red

* Para dar acesso as portas pode ser feito direto do serviço que está utilizando (na Azure, por exemplo) ou se for maquina virtual própria usar o comando:

```bash
sudo ufw allow <porta>/tcp
```


![Esquematização da simulação da ponte H no tinkercad](https://github.com/guta231/modelismo-carro-eletrico/blob/main/Simulção%20de%20funcionamento%20de%20controle%20de%20motores%20com%20ponte%20H.png)

Clique [aqui](https://www.tinkercad.com/things/435US7UQ3Br-simulcao-de-funcionamento-de-controle-de-motores-com-ponte-h/editel?sharecode=-I9c74cXKC-TmST46V9TmLGtamamGN4YTIUSaphgF8g) para ver a simulação do funcionamento de uma ponte H no tinkercad.
