<div align="center" >
  <img src="https://game.42sp.org.br/static/assets/achievements/pipexm.png" alt="Pipex" width="175" height="175">
  <h1><i>Fase 1</h1></i>

</div>

# :trophy: Score
> Na 42, a parte mandatória dos projetos são avaliadas de 0 a 100, há uma nota mínima necessária para que a pessoa seja aprovada, mas que varia dependendo da dificuldade do projeto. Caso a pessoa faça o bônus, a nota será de 101 a 125.

<div align="center" >
  <img src="./grade.png" alt="grade">

</div>


# :information_source: About
> O projeto pipex é uma recriação do comando pipe do shell, que é um comando que permite a comunicação entre dois processos, onde a saída de um comando é a entrada para o próximo. Além disso, também era necessário implemenntar a lógica dos operadores de redirecionamento '<' e '>', que são usados para redirecionar a entrada do stdin e a saída do stdout para um arquivo, respectivamente. 

> Para fazer o Pipex, somos apresentados a algumas funções novas, como a **dup2()**, que permite a duplicação de um file descriptor, a **execve()**, que executa um programa, e a **fork()**, que cria um processo filho. Além disso, também é necessário o uso de pipes, que são usados para a comunicação entre os processos. Nesse projeto você irá aprender conceitos de processos, file descriptors, pipes e execução de programas.


# :books: Objetivos
> Em relação ao projeto, no mandatório precisamos criar um programa que receba 4 argumentos, o primeiro é o arquivo de entrada, o segundo é o comando 1, o terceiro é o comando 2 e o quarto é o arquivo de saída. O programa deve executar o comando 1 com o arquivo de entrada, e o comando 2 com a saída do comando 1, e por fim, deve salvar a saída do comando 2 no arquivo de saída. Os argumentos serão parecidos com esse:

```bash
./pipex infile "cat" "wc -l" outfile
```

> Os argumentos acima devem funciona da mesma forma quando jogamos esse comando no shell:

```bash

< infile cat | wc -l > outfile

```

> Já o bônus é dividido em duas partes. A primeira é a implementação de um número ilimitado de comandos (aka múltiplos pipes), e a segunda é a implementação de parte do heredoc, mais especificamente, apenas a variante dos operadores de redirecionamento '<<' e '>>', além do delimitador. No heredoc, o operador '<<' é usado para redirecionar a entrada do stdin para um comando, isso é parte da sintáxe básica ao usar o heredoc. Já o operador '>>' é usado para redirecionar a saída do stdout para um arquivo, muito semelhante ao que o operador '>' faz, entretanto a diferença é que o operador '>>' não sobrescreve o conteúdo do arquivo, ele apenas adiciona a saída do stdout no final do arquivo. Abaixo estão as formas de utilizar os argumentos com múltiplos pipes e heredoc:

> Multi pipes:
```bash
./pipex_bonus infile "cat" "cmd1" "cmd2" "cmd3" "cmd4" "cmdN" outfile
```
> O comando acima é equivalente a esse comando no shell:
```bash
< infile cat | cmd1 | cmd2 | cmd3 | cmd4 | cmdN > outfile
```

> Heredoc:
```bash
./pipex_bonus here_doc LIMITER "cmd1" "cmd2" "cmd3" "cmdN" outfile
```

> O comando do heredoc do shell é esse:
```bash
cmd1 << LIMITER cmd2 | cmd3 | cmdN >> outfile
```

# :video_game: Principais funções utilizadas
> No subject há uma lista de funções que você pode usar, mas eu vou listar aqui as principais funções que eu usei no projeto, e que eu acho que são as mais importantes para você entender o projeto. Confira a lista abaixo:

| Função | Descrição |
| ------ | --------- |
| pipe() | Cria um pipe, que é usado para a comunicação entre processos. |
| fork() | Cria um processo filho. Um processo filho é um processo que é criado a partir de um processo pai, e ele herda todas as variáveis do processo pai. |
| dup2() | Duplica um file descriptor, ou seja, ele copia um file descriptor para outro. Isso funciona como um redirecionamento de file descriptor. |
| execve() | Executa um programa. Por baixo dos panos, o execve() é uma função que chama o programa que você quer executar, e ele substitui o processo atual pelo processo do programa que você quer executar. |
| wait() | Espera um processo filho terminar. Ele é mais básico que o waitpid(), e ele espera qualquer processo filho terminar. |

# :tests: Testes
> Nesse projeto voltei a utilizar a Minunit e dessa vez aprimorei ela. Especificamente para esse projeto eu criei uma função que executa tanto o pipex quanto o comando equivalente no shell, daí utilizando funções da própria minilibx, eu comparo a saída do pipex com a saída do comando equivalente no shell. Nos testes ele retornará verdadeiro, se as saídas forem iguais ou falso, se as saídas forem diferentes. Nesse caso inclusive, irá mostrar exatamente qual foi a diferença. 

> Outra atualização na minilibx é que agora é possível rodar todos os testes de uma vez só. Para fins de legibilidade eu separei 1 teste para arquivo, assim essa funcionalidade funciona de uma forma mais fácil. Para usar os testes, basta rodar o comando abaixo:

```bash
make
```

> O comando make irá compilar os arquivos dos testes e também chamará o make do makefile do pipex, que consequentemente chamará da libft, ou seja, um makefile chama outro que chama outro, kk. Depois de compilar, todos os testes terão o seus arquivos objetos gerados. Daí você pode tanto fazer testes individualizados, executando o teste dessa forma:

```bash
./test_name
```

> Como pode rodar todos os testes de uma vez, usando esse comando:

```bash
make test
```

> **OBS:** Nos testes apenas implementei o mandatório, o bônus não foi implementado. Para os testes relcionados ao bônus eu acabei testando na mão, mas para funcionar com o minunit da mesma forma que o mandatório, seria necessário adaptar o makefile para compilar os arquivos do pipex bônus. Talvez futuramente eu acrescente essa funcionalidade.

