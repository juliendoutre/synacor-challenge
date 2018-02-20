all: vm.out

vm.out: vm/main.c vm/stack.c vm/utils.c
	gcc vm/main.c vm/stack.c vm/utils.c -o vm.out

mrproper:
	rm -rf vm.out
