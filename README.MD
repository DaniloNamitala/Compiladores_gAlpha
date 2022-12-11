#  Desk Lang

## Integrantes
- Danilo Aparecido Namitala - 202011125 
- Henrique Silva Rabelo - 202010698
- Jhonatan Gardioli Lourenço - 20190247
- Pedro H. dos Santos M. 201910948
- Pedro H. M. Alves - 201920257


## Descrição: 
<b>Desk Lang</b> é uma linguagem de alto nível que busca se aproximar do que seria um pseudocódigo, podendo ser usada para mostrar explicações simples, em substituição ao pseudocódigo, mas com a possibilidade de poder ser compilada e executada. 

## Extensão de arquivo da linguagem
    .dskl

`arquivo.dskl`

## Orientações para uso

Para execução analisador léxico preciso rodar o comando:
```
make
```

Nesse momento a classe a partir da gramatica que foi criada para a linguagem vai ser gerada automaticamente. 

Caso seja feito mais alguma alteração no `main.cpp` é necessário executar o comando acima novamente.

Após o `make`, foi criado o arquivo executável do programa em c++, com isso é possível fazer a análise léxica dos arquivos com o comando `./main [nome_arquivo]`, como por exemplo:

```
./main ../fatorial.dskl
```

Com isso é esperado o retorno da análise léxica do seu programa.
