all: vm.out

vm.out: vm/main.c vm/stack.c vm/utils.c vm/decipher.c
	gcc vm/main.c vm/stack.c vm/utils.c vm/decipher.c -o vm.out

mrproper:
	rm -rf vm.out
