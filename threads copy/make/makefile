DIR=arquivos/

OPT=-wall
NAME=helloWorld
PROGRAMAS=hello.o world.o helloWorld

# Targes
# Estes funcionam como um meio de criar setups diferentes para um mesmo make
# Com isso, podemos criar várias combinações de compilação
all: hello world main
	echo "Compilando tudo"
	hello
	world
	main
	
hello: $(DIR)hello.c
	echo "Compilando lib hello"
	gcc $(DIR)hello.c -c

world: $(DIR)world.c
	echo "Compilando lib world"
	gcc $(DIR)world.c -c
	
main: $(DIR)main.c
	echo "Compilando main"
	gcc $(DIR)main.c hello.o world.o -o $(NAME)

clean:
	rm $(PROGRAMAS)