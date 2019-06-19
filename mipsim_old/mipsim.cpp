/* ****************************************************************
   MIPS32 Instruction Set Simulator
   Computer Architecture, Semester 1, 2016

   Main program

**************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>

#include "memory.h"
#include "cache.h"
#include "processor.h"
#include "commands.h"

using namespace std;

int main(int argc, char* argv[]) {

  // Values of command line options. 
  string arg;
  bool verbose = false;
  bool cycle_reporting = false;
  unsigned long int icache_block_size = 0, icache_size = 0, icache_associativity = 0;
  unsigned long int dcache_block_size = 0, dcache_size = 0, dcache_associativity = 0;
  bool dcache_write_through = false;
  bool dcache_write_back = false;
  unsigned long int memory_address_cycles = 0, memory_word_cycles = 0;
  bool icache_full_associativity = false, dcache_full_associativity = false;
  bool icache_present = false;
  bool dcache_present = false;
  cache::write_strategy_t dcache_write_strategy;
  bool options_error = false;

  memory* main_memory;
  memory_accessible* icache;
  memory_accessible* dcache;
  processor* cpu;


  for (int i = 1; i < argc; i++) {
    // Process the next option
    arg = string(argv[i]);
    if (arg == "-v")  // Verbose output
      verbose = true;
    else if (arg == "-c")  // Cycle and instruction reporting enabled
      cycle_reporting = true;
    else if (arg == "-ib") {  // Icache cache block size in bytes
      i++;

      icache_block_size = atoi(argv[i]);
    }
    else if (arg == "-is") {  // Icache cache size in Kbytes
      i++;
      icache_size = atoi(argv[i]);
    }
    else if (arg == "-ia") {  // Icache cache associativity
      i++;
      if (string(argv[i]) == "full")  // Calculate later using cache size and block size
	icache_full_associativity = true;
      else
	icache_associativity = atoi(argv[i]);
    }
    else if (arg == "-db") {  // Dcache cache block size in bytes
      i++;
      dcache_block_size = atoi(argv[i]);
    }
    else if (arg == "-ds") {  // Dcache cache size in Kbytes
      i++;
      dcache_size = atoi(argv[i]);
    }
    else if (arg == "-da") {  // Dcache cache associativity
      i++;
      if (string(argv[i]) == "full")  // Calculate later using cache size and block size
	dcache_full_associativity = true;
      else
	dcache_associativity = atoi(argv[i]);
    }
    else if (arg == "-dwt") {  // Dcache is write-through
      dcache_write_through = true;
      dcache_write_strategy = cache::WRITE_THROUGH;
    }
    else if (arg == "-dwb") {  // Dcache is write-through
      dcache_write_back = true;
      dcache_write_strategy= cache::WRITE_BACK;
    }
    else if (arg == "-ma") {  // Cycles for address access in memory
      i++;
      memory_address_cycles = atoi(argv[i]);
    }
    else if (arg == "-mw") {  // Cycles per word access in memory
      i++;
      memory_word_cycles = atoi(argv[i]);
    }
    else {
      cout << "Unknown option: " << arg << endl;
      options_error = true;
    }
  }

  // If associativity is full, calculate using cache size and block size
  if (icache_full_associativity && icache_block_size != 0) {
    icache_associativity = (icache_size * 1024) / icache_block_size;
  }
  if (dcache_full_associativity && dcache_block_size != 0) {
    dcache_associativity = (dcache_size * 1024) / dcache_block_size;
  }

  // If any Icache options specified, Icache is present
  icache_present = (icache_block_size != 0 || icache_size != 0 || icache_associativity != 0);

  // If any Dcache options specified, Dcache is present
  dcache_present = (dcache_block_size != 0 || dcache_size != 0 || dcache_associativity != 0 ||
		    dcache_write_through || dcache_write_back);

  // Check for missing or invalid options
  if (icache_present) {
    if (icache_block_size == 0 || icache_size == 0 || icache_associativity == 0) {
      cout << "Missing option, all of -ib, -is, -ia required if Icache is present" << endl;
      options_error = true;
    }
    if ((icache_size & (icache_size - 1)) ||
	(icache_block_size & (icache_block_size - 1)) ||
	(icache_associativity & (icache_associativity - 1))) {
      cout << "ICache size, block size and associativity must all be powers of 2" << endl;
      options_error = true;
    }
    if (icache_block_size * icache_associativity > icache_size * 1024) {
      cout << "Icache size must be at least block size times associativity" << endl;
      options_error = true;
    }
  }
  if (dcache_present) {
    if (dcache_block_size == 0 || dcache_size == 0 || dcache_associativity == 0) {
      cout << "Missing option, all of -db, -ds, -da required if Dcache is present" << endl;
      options_error = true;
    }
    if (!dcache_write_through && !dcache_write_back) {
      cout << "Missing option, one of -dwt or -dwb required if Dcache is present" << endl;
      options_error = true;
    }
    if (dcache_write_through && dcache_write_back) {
      cout << "Only one of -dwt or -dwb allowed if Dcache is present" << endl;
      options_error = true;
    }
    if ((dcache_size & (dcache_size - 1)) ||
	(dcache_block_size & (dcache_block_size - 1)) ||
	(dcache_associativity & (dcache_associativity - 1))) {
      cout << "DCache size, block size and associativity must all be powers of 2" << endl;
      options_error = true;
    }
    if (dcache_block_size * dcache_associativity > dcache_size * 1024) {
      cout << "Dcache size must be at least block size times associativity" << endl;
      options_error = true;
    }
  }
  if (cycle_reporting &&
      (memory_address_cycles == 0 || memory_word_cycles == 0)) {
    cout << "Missing option, -ma and -mw required with -c for cycle reporting" << endl;
    options_error = true;
  }

  if (options_error) {
    return 1;  // Non-zero exit code indicates error
  }    

  if (verbose) {
    // Display summary of cache options
    if (icache_present) {
      cout << "Icache: size = " << dec << icache_size <<
	"KB, block size = " << dec << icache_block_size <<
	", associativity = " << dec << icache_associativity << endl;
    }
    if (dcache_present) {
      cout << "Dcache: size = " << dec << dcache_size <<
	"KB, block size = " << dec << dcache_block_size <<
	", associativity = " << dec << dcache_associativity << endl;
    }
    if (cycle_reporting) {
      cout << "Memory: address access cycles = " << dec << memory_address_cycles <<
	", word access cycles = " << dec << memory_word_cycles << endl;
    }
  }

  main_memory = new memory (verbose, cycle_reporting, memory_address_cycles, memory_word_cycles);
  if (icache_present) {
    icache = new cache ("Instruction cache", main_memory,
			icache_block_size, icache_size * 1024, icache_associativity,
			cache::READ_ONLY, verbose);
  } else {
    icache = main_memory;
  }
  if (dcache_present) {
    dcache = new cache ("Data cache", main_memory,
			dcache_block_size, dcache_size * 1024, dcache_associativity,
			dcache_write_strategy, verbose);
  } else {
    dcache = main_memory;
  }
  cpu = new processor (icache, dcache, verbose);

  interpret_commands(main_memory, cpu, verbose);

  unsigned long int cpu_instruction_count;
    
  cpu_instruction_count = cpu->get_instruction_count();
  cout << "Instructions executed: " << dec << cpu_instruction_count << endl;

  // Report final statistics
  if (icache_present)
    icache->report_accesses();
  if (dcache_present)
    dcache->report_accesses();

  if (cycle_reporting) {
    // Required for postgraduate Computer Architecture course
    unsigned long int cpu_cycle_count;
    unsigned long int main_memory_cycle_count;

    cpu_cycle_count = cpu->get_cycle_count();
    main_memory->report_accesses();
    main_memory_cycle_count = main_memory->get_read_cycle_count();

    cout << "CPU cycle count: " << dec << cpu_cycle_count << endl;
    cout << "Stall cycles accessing memory: " << dec << main_memory_cycle_count << endl;
    cout << "Average CPI (ideal): "
	 << fixed << setprecision(6)
	 << (double)cpu_cycle_count / (double)cpu_instruction_count << endl;
    cout << "Average CPI (actual): "
	 << fixed << setprecision(6)
	 << ((double)cpu_cycle_count + (double)main_memory_cycle_count) / (double)cpu_instruction_count
	 << endl;
  }
}
