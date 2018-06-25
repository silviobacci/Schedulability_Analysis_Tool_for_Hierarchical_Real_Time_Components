#ifndef VM_IO_H
#define VM_IO_H

#include <vm/structs/cpu.h>
#include <vm/structs/vm.h>

vm * create_empty_vm();
vm * load_vm(FILE *f);

#endif
