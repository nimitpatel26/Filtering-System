cc = gcc
all: d1 d2 d3 d4 d5 d6 d7 d8 d9 d10 d11 d12

d1: 335_fw421_reset.c
	$(cc) 335_fw421_reset.c -o fw421_reset

d2: 336_fw421_block_port.c
	$(cc) 336_fw421_block_port.c -o fw421_block_port

d3: 337_fw421_unblock_port.c
	$(cc) 337_fw421_unblock_port.c -o fw421_unblock_port

d4: 338_fw421_query.c
	$(cc) 338_fw421_query.c -o fw421_query

d5: 339_fc421_reset.c
	$(cc) 339_fc421_reset.c -o fc421_reset

d6: 340_fc421_block_file.c
	$(cc) 340_fc421_block_file.c -o fc421_block_file

d7: 341_fc421_unblock_file.c
	$(cc) 341_fc421_unblock_file.c -o fc421_unblock_file

d8: 342_fc421_query.c
	$(cc) 342_fc421_query.c -o fc421_query

d9: debug_343_fw421_check_blocked.c
	$(cc) debug_343_fw421_check_blocked.c -o debug_fw421_check_blocked

d10: debug_344_fc421_check_blocked.c
	$(cc) debug_344_fc421_check_blocked.c -o debug_fc421_check_blocked

d11: debug_345_fw421_print_ports.c
	$(cc) debug_345_fw421_print_ports.c -o debug_fw421_print_ports

d12: debug_346_fc421_print_files.c
	$(cc) debug_346_fc421_print_files.c -o debug_fc421_print_files

clean:
	rm *.c~
