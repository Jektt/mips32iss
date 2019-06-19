#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <cstdio>
#include <string>

#include "processor.h"

processor::processor(memory_accessible* icache,
	    memory_accessible* dcache,
	    bool verbose) {

  breakpoint_set = false;
  m_verbose = verbose;
  m_icache = icache;
  m_dcache = dcache;
  PC = 0x00000000;
  m_instructioncount = 0;
  Reg = new uint32_t[32]();
  branchAddr = 0;
  setBranch = false;
}

  // Display PC value
  void processor::show_pc()
  {
	cout << setfill('0') << setw(8) << hex << PC << endl;
  }

  // Set PC to new value
  void processor::set_pc(uint32_t new_pc)
  {
	if (m_verbose)
		cout << "DEBUG: Setting new PC to: " << setfill('0') << setw(8) << hex << new_pc << endl;
	PC = new_pc;
  }
  // Display register value
  void processor::show_reg(unsigned int reg_num)
  {
	if (m_verbose)
		cout << "Value in register #" << dec << reg_num << " is: 0x" << setfill('0') << setw(8) << hex << Reg[reg_num] << endl;	
	cout << setfill('0') << setw(8) << hex << Reg[reg_num] << endl;
  }

  // Set register to new value
  void processor::set_reg(unsigned int reg_num, uint32_t new_value)
  {
	if (m_verbose)
		cout << "DEBUG: Value in register #" << dec << reg_num << " changed to: 0x" << setfill('0') << setw(8) << hex << new_value << endl;
	if (reg_num != 0)
		Reg[reg_num] = new_value;
  }

  // Execute a number of instructions
  void processor::execute(unsigned int num, bool breakpoint_check) 
  {
	unsigned int n_count = 0;

	while(n_count < num)
	{

		if (breakpoint_check && breakpoint_set)
		{	
			if (PC == breakpoint) 
			{
				cout << "Breakpoint reached at " << setfill('0') << setw(8) << hex << breakpoint << endl;
				return;
			}
		}

		if (setBranch)
		{
			set_pc(branchAddr - 4);
			setBranch = false;
		}		

		if ((PC % 4 ) != 0) {
			cout << "Unaligned pc: " << setfill('0') << setw(8) << hex << PC << endl;
			return;
		}

		uint32_t inst = m_icache->read_word(PC);
		if (m_verbose)
			cout << "DEBUG: Instruction in PC is: " << setfill('0') << setw(8) << hex << inst << endl;
	
		// get the bit fields from the instruction
		set_bitfields(inst);
	
		// get the instruction mneumonic and thus call the function to execute that instruction
		char instType;
		string instMnemonic;

		if (m_verbose)
		{
			cout << "DEBUG: Value in opcode is: " << setfill('0') << setw(8) << hex << m_opcode << endl;
		}

		if (m_opcode == 0x00) {
			if (m_verbose) 
				cout << "DEBUG: R Type Instruction" << endl;
			instType = 'R';
		}

		else if (m_opcode == 0x02)
		{
			if (m_verbose)
				cout << "DEBUG: J Type Instruction (j mneumonic)" << endl;
			instType = 'J';
			instMnemonic = "j";
		}

		else if (m_opcode == 0x03)
		{
			if (m_verbose)
				cout << "DEBUG: J Type Instruction (jal mneumonic)" << endl;
			instType = 'J';
			instMnemonic = "jal";
		}

		else {
			if (m_verbose)
				cout << "DEBUG: I Type Instruction" << endl;
			instType = 'I';
		}
		
		if (instType == 'I')
		{
			switch (m_opcode)
			{
				case 0x2B:
				{
					// MEM[$s + offset] = $t; advance_pc (4);
					instMnemonic = "sw";
					int16_t s_imm = m_immediate;
					m_icache->write_word(Reg[m_rs] + s_imm, Reg[m_rt], 0xFFFFFFFF);
					set_pc(PC+4);
					break;
				}
				case 0x0E:
				{
					instMnemonic = "xori";
					if (m_rt != 0)
					{
						uint32_t ext_imm = m_immediate;		// 0s to the left 
						Reg[m_rt] = Reg[m_rs] ^ ext_imm;
					}
					set_pc(PC+4);
					break;
				}
				case 0x0A:
				{
					instMnemonic = "slti";
					// if $s < imm $t = 1; advance_pc (4); else $t = 0; advance_pc (4);
					// sign extend m_immediate
					if (m_rt != 0)
					{
						int16_t temp = m_immediate;
						int32_t s_imm = temp;
						int32_t s_rs = Reg[m_rs];
						if (s_rs < s_imm)
							Reg[m_rt] = 1;
						else 
							Reg[m_rt] = 0;
					}
					set_pc(PC+4);
					break;
				}
				case 0x0B:
				{
					// sign extend m_immediate
					int16_t temp = m_immediate;
					int32_t temp2 = temp;
					uint32_t u32_imm = temp2;
					instMnemonic = "sltiu";
					if (m_rt != 0)
					{
						if (Reg[m_rs] < u32_imm)
							Reg[m_rt] = 1;
						else
							Reg[m_rt] = 0;
					}
					set_pc(PC+4);
					break;
				}
				case 0x23:
				{
					// $t = MEM[$s + offset]; advance_pc (4);
					instMnemonic = "lw";
					int16_t imm = m_immediate;
					if (m_rt != 0)
						Reg[m_rt] = m_icache->read_word(Reg[m_rs] + imm);
					set_pc(PC+4);
					break;
				}
				case 0x08:
				{
					instMnemonic = "addi";
					// signed instruction
					int16_t temp = m_immediate;
					int32_t imm_32s = temp;		// sign extend to 32 bits
					int32_t rs_s = Reg[m_rs];
					if (m_rt != 0)
						Reg[m_rt] = rs_s + imm_32s;
					set_pc(PC+4);
					break;
				}
				case 0x0D:
				{
					instMnemonic = "ori";
					if (m_rt != 0)
					{
						uint32_t ext_imm = m_immediate;		// 0s to the left 
						Reg[m_rt] = Reg[m_rs] | ext_imm;
					}
					set_pc(PC+4);
					break;
				}
				case 0x0C:
				{
					
					instMnemonic = "andi";
					if (m_rt != 0)
					{
						uint32_t ext_imm = m_immediate;		// 0s to the left 
						Reg[m_rt] = Reg[m_rs] & ext_imm;
					}
					set_pc(PC+4);
					break;
				}
				case 0x09:
				{
					instMnemonic = "addiu";
					// immediate value should be sign extended to 32 bits
					int16_t temp = m_immediate;
					int32_t imm_32s = temp;
					if (m_rt != 0)
						Reg[m_rt] = Reg[m_rs] + imm_32s;
					set_pc(PC+4);
					break;					
				}
				case 0x0F:
				{
					instMnemonic = "lui";
					uint32_t temp = m_immediate << 16;
					Reg[m_rt] = temp;
					set_pc(PC+4);
					break;
				}
				case 0x05:
				{
					instMnemonic = "bne";
					if (Reg[m_rs] != Reg[m_rt])
					{
						setBranch = true;
						// check if displacement is negative
						if (0x8000 & m_immediate) 
						{
							int16_t temp = m_immediate;			// sign extending? Tried didnt fix it
							branchAddr = (PC+4) + (temp * 4);
						}
						else
							branchAddr = (PC+4) + (m_immediate * 4);
					}
					set_pc(PC+4);
					break;
				}
				default:
				{
					// no valid I instruction detected
					set_pc(PC+4);
					break;
				}
			}
		}

		else if (instType == 'R')
		{
			// we have all the fields already and we know its an R instruction, check funct to determine which instruction
			switch (m_funct) 
			{
				case 0x20:
				{
					instMnemonic = "add";
					int32_t ts_rs = Reg[m_rs];
					int32_t ts_rt = Reg[m_rt];
					int32_t ts_result = ts_rs + ts_rt;
					if (m_rd != 0)
						Reg[m_rd] = ts_result;
					set_pc(PC+4);
					break;
				}
				case 0x21: 
				{
					instMnemonic = "addu";
					Reg[m_rd] = Reg[m_rs] + Reg[m_rt];
					set_pc(PC+4);
					break;
				}
				case 0x24:
				{
					instMnemonic = "and";
					if (m_rd != 0)
						Reg[m_rd] = Reg[m_rs] & Reg[m_rt];
					set_pc(PC+4);
					break;
				}
				case 0x09:
				{
					instMnemonic = "jalr";
					Reg[m_rd] = PC + 4;		// @@ possibly + 8?
					setBranch = true;
					branchAddr = Reg[m_rs];
					set_pc(PC+4);
					break;
				}
				case 0x08:
				{
					instMnemonic = "jr";
					setBranch = true;
					branchAddr = Reg[m_rs];
					set_pc(PC+4);
					break;
				}
				case 0x27:
				{
					instMnemonic = "nor";
					if (m_rd != 0)
						Reg[m_rd] = ~(Reg[m_rs] | Reg[m_rt]);
					set_pc(PC+4);
					break;
				}
				case 0x25:
				{
					instMnemonic = "or";
					if (m_rd != 0)
						Reg[m_rd] = Reg[m_rs] | Reg[m_rt];
					set_pc(PC+4);
					break;
				}
				case 0x00:
				{
					instMnemonic = "sll";
					if (m_rd != 0)
						Reg[m_rd] = Reg[m_rt] << m_shamnt;
					set_pc(PC+4);
					break;
				}
				case 0x2a:
				{
					instMnemonic = "slt";
					int32_t ts_rs = Reg[m_rs];
					int32_t ts_rt = Reg[m_rt];
					if (ts_rs < ts_rt)
					{
						if (m_rd != 0)
							Reg[m_rd] = 1;
					}
					else
						Reg[m_rd] = 0;
					set_pc(PC+4);
					break;
				}
				case 0x2b:
				{
					instMnemonic = "sltu";
					if (Reg[m_rs] < Reg[m_rt])
					{
						if (m_rd != 0)
							Reg[m_rd] = 1;
					}
					else
						Reg[m_rd] = 0;
					set_pc(PC+4);
					break;
				}
				case 0x03:
				{
					instMnemonic = "sra";
					int32_t ts_rt = Reg[m_rt];
					if (ts_rt < 0)
					{
						if (m_rd != 0)
							Reg[m_rd] = ts_rt >> m_shamnt;
					}
					else 
					{
						if (m_rd != 0)
							Reg[m_rd] = Reg[m_rt] >> m_shamnt;
					}
					set_pc(PC+4);
					break;
				}
				case 0x02:
				{
					instMnemonic = "srl";
					if (m_rd != 0)
						Reg[m_rd] = Reg[m_rt] >> m_shamnt;
					set_pc(PC+4);
					break;
				}
				case 0x22:
				{
					instMnemonic = "sub";
					int32_t ts_rs = Reg[m_rs];
					int32_t ts_rt = Reg[m_rt];
					int32_t ts_result = ts_rs - ts_rt;
					if (m_rd != 0)
						Reg[m_rd] = ts_result;
					set_pc(PC+4);
					break;
				}
				case 0x23:
				{
					instMnemonic = "subu";
					if (m_rd != 0) 
					{
						Reg[m_rd] = Reg[m_rs] - Reg[m_rt];
					}
					set_pc(PC+4);
					break;
				}
				case 0x26:
				{
					instMnemonic = "xor";
					if (m_rd != 0) 
						Reg[m_rd] = Reg[m_rs] ^ Reg[m_rt];
					set_pc(PC+4);
					break;
				}
				default:
				{
					cout << "Fatal Error." << endl;
					if (m_verbose)
						cout << "DEBUG: Error determing R instruction mnemonic from funct field." << endl;
					break;
				}
			}

		}
		if (m_verbose) 
			cout << "DEBUG: The instruction mnemonic is: " << instMnemonic << endl;
		n_count++;
  		m_instructioncount++;
		if (m_verbose)
  			cout << "DEBUG: At bottom of while loop. m_instructioncount = " << m_instructioncount << endl;
	}

  }

  void processor::set_bitfields(uint32_t inst)
  {
	uint32_t opMask = 		0xfc000000;
	uint32_t rsMask = 		0x03e00000;
	uint32_t rtMask = 		0x001f0000;
	uint32_t rdMask = 		0x0000f800;
	uint32_t shamntMask = 		0x000007c0;
	uint32_t functMask = 		0x0000003f;
	uint32_t immediateMask = 	0x0000FFFF;
	uint32_t addressMask =  	0x03FFFFFF;	

	m_opcode = (inst & opMask) >> 26;
	m_rs = (inst & rsMask) >> 21;
	m_rt = (inst & rtMask) >> 16;
	m_rd = (inst & rdMask) >> 11;
	m_shamnt = (inst & shamntMask) >> 6;
	m_funct = (inst & functMask);
	m_immediate = (inst & immediateMask);
	m_address = (inst & addressMask);

	if (m_verbose)
	{
		cout << "DEBUG:  opcode (dec): " << dec << m_opcode << endl;
		cout << "DEBUG:  rs (dec): " << dec << m_rs << endl;
		cout << "DEBUG:  rt (dec): " << dec << m_rt << endl;
		cout << "DEBUG:  rd (dec): " << dec << m_rd << endl;
		cout << "DEBUG:  shamnt (dec): " << dec << m_shamnt << endl;
		cout << "DEBUG:  funct (dec): " << dec << m_funct << endl;
		cout << "DEBUG:  immediate (dec): " << dec << m_immediate << endl;
		cout << "DEBUG:  address (dec): " << dec << m_address << endl;
	}
  } 

  // Clear breakpoint
  void processor::clear_breakpoint() 
  {
	if (m_verbose)
		cout << "DEBUG: Clearing the breakpoint" << endl;
	breakpoint = 0;		// we cant clear it. There is always going to be some 32 bit value here that PC could happen to equal
	breakpoint_set = false;
  }

  // Set breakpoint at an address
  void processor::set_breakpoint(uint32_t address)
  {
	breakpoint_set = true;
	breakpoint = address;
  }

  // Probe the instruction cache interface for an address
  void processor::probe_instruction (uint32_t address) 
  {
	// not needed for stage 1
  }

  // Probe the data cache interface for an address
  void processor::probe_data (uint32_t address)
  {
	// not needed for stage 1
  }

  uint64_t processor::get_instruction_count() {
	return m_instructioncount;
  }

  uint64_t processor::get_cycle_count() {
	// not needed for UG
	uint64_t temp = 0;
	return temp; 
  }
