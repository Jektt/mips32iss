#ifndef PROCESSOR_H
#define PROCESSOR_H

/* ****************************************************************
   MIPS32 Instruction Set Simulator
   Computer Architecture, Semester 1, 2016

   Class for processor

**************************************************************** */

#include "memory_accessible.h"

using namespace std;

class processor {

 private:

	// registers and PC
	uint32_t PC;
	uint32_t* Reg;
	memory_accessible* m_icache;
	memory_accessible* m_dcache;
	bool m_verbose;
	uint32_t breakpoint;
	bool breakpoint_set;
	uint64_t m_instructioncount;
	uint32_t branchAddr;
	bool setBranch;
   	bool letsJump;

	// address bitfields
	uint32_t m_opcode;
	uint32_t m_rs;
	uint32_t m_rt;
	uint32_t m_rd;
	uint32_t m_shamnt;
	uint32_t m_funct;
	uint16_t m_immediate;
	uint32_t m_address;

 public:

  // Consructor
  processor(memory_accessible* icache,
	    memory_accessible* dcache,
	    bool verbose);

  // Display PC value
  void show_pc();

  void set_bitfields(uint32_t address);

  // Set PC to new value
  void set_pc(uint32_t new_pc);

  // Display register value
  void show_reg(unsigned int reg_num);

  // Set register to new value
  void set_reg(unsigned int reg_num, uint32_t new_value);

  // Execute a number of instructions
  void execute(unsigned int num, bool breakpoint_check);

  // Clear breakpoint
  void clear_breakpoint();

  // Set breakpoint at an address
  void set_breakpoint(uint32_t address);

  // Probe the instruction cache interface for an address
  void probe_instruction (uint32_t address);

  // Probe the data cache interface for an address
  void probe_data (uint32_t address);

  uint64_t get_instruction_count();

  uint64_t get_cycle_count();

};

#endif
