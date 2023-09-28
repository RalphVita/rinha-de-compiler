# Rinha de Compiler
[Rinha da Compiladores](https://github.com/aripiprazole/rinha-de-compiler)


## Build
```shell
cd ./build
cmake ..
make
```
## Exemplo
```shell
./main ../source.rinha.json
```

## Testes Unitários
```shell
cd ./build
cmake ..
make test
```

## Docker
```shell
docker build .
docker run -v $(pwd):/var/rinha/ --memory=2gb --cpus=2 nome_da_imagem
```
Espera-se que em *$(pwd)*, tenha um arquivo *source.rinha.json*, que será interpretado. 

## Habilitar Trace
Habilitar trace para 'debug'.
```shell
cd ./build
cmake .. -DCMAKE_SHOW_TRACE=True
make
```
