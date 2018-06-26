#ifndef VM_IO_H
#define VM_IO_H

#include <vm/structs/cpu.h>
#include <vm/structs/vm.h>

void print_vm(vm *v, FILE *f);
void print_vm_load(vm *v, FILE *f);
vm * create_empty_vm();
vm * load_vm(FILE *f);

#endif
