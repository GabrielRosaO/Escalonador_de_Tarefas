# Escalonador_de_Tarefas
Este é um projeto da disciplina de Sistemas Operacionais. 
A ideia do projeto é construir um Escalonador de Arquivos, na linguagem C utilizando do método SJF(Shortest Job First).
Esse método executa as tarefas de acordo com a que tiver menor tempo necessário para execução.

### Descrição do Projeto
É passado um arquivo de texto com o nome e tempo necessário de execução para cada tarefa. 
A disposição deles no arquivo é a seguinte: 
Exemplo - tarefas.txt
```
a1 5
a2 1
a3 10
b1 10
b2 3
b3 7
b4 8
c1 8
c2 2
c3 9
```
O código lê esse arquivo e gera outro arquivo de texto como resposta, result.txt.
No arquivo de resultado a disposição das tarefas é:
```
Processador [i]
tarefa1;tempo_de_inicio;tempo_de_término;
tarefa2;tempo_de_inicio;tempo_de_término;
tarefa3;tempo_de_inicio;tempo_de_término;
Processador[i+1]
tarefa4;tempo_de_inicio;tempo_de_término;
tarefa5;tempo_de_inicio;tempo_de_término;
tarefa6;tempo_de_inicio;tempo_de_término;
```
### Execução do código
Para executar o código é preciso passar o arquivo de texto com as tarefas e o número de processadores a ser utilizado.
Para compilação do código:
```
gcc trabalho_escalonador -o 'nome_executável'
```
Um exemplo de execução do código com 2 processadores e arquivo de texto com as tarefas como 'tarefas.txt', no Windows:
```
./'nome_executável' tarefas.txt 2
```
