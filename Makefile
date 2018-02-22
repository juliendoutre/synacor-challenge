all: vm.app

vm.app: vm/main.c vm/stack.c vm/utils.c vm/decipher.c
	gcc vm/main.c vm/stack.c vm/utils.c vm/decipher.c -o vm.app

mrproper:
	rm -rf vm.app
