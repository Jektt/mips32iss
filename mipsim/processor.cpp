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
  instMnemonic = "";
  instType = '0';
  jumpLink = false;
  savedAddress = 0;
  b_count = 0;
}

// Display PC value
void processor::show_pc()
{
	cout << setfill('0') << setw(8) << hex << PC << endl;
}

// Set PC to new value
void processor::set_pc(uint32_t new_pc)
{
	PC = new_pc;
}
  
// Display register value
void processor::show_reg(unsigned int reg_num)
{	
	cout << setfill('0') << setw(8) << hex << Reg[reg_num] << endl;
}

// Set register to new value
void processor::set_reg(unsigned int reg_num, uint32_t new_value)
{
	//cout << "SETTING REGISTER NUMBER: " << reg_num << ", TO VALUE: " << hex << setfill('0') << setw(8) << new_value << endl;
	if (reg_num != 0)
		Reg[reg_num] = new_value;
}

  // Execute a number of instructions
void processor::execute(unsigned int num, bool breakpoint_check) 
{
	// Could be worthwhile sorting the memory_list here relative to virtual base address of each block
	// Would only be beneficial for very large programs. Actually made the compiled tests much slower
	
	unsigned int n_count = 0;

	while(n_count < num)
	{
		
		if ((PC % 4 ) != 0) 
		{
			cout << "Unaligned pc: " << setfill('0') << setw(8) << hex << PC << endl;
			return;
		}
		
		if (setBranch)
			b_count++;

		if (breakpoint_check && breakpoint_set)
		{	
			if (PC == breakpoint) 
			{
				cout << "Breakpoint reached at " << setfill('0') << setw(8) << hex << breakpoint << endl;
				return;
			}
		}

		// get the instruction we want to execute
		uint32_t inst = m_icache->read_word(PC);
		//cout << "EXECUTING THE INSTRUCTION: " << hex << setfill('0') << setw(8) << inst << endl; 
		if (m_verbose)
			cout << "Fetch: pc = " << setfill('0') << setw(8) << hex << PC << ", ir = " << setfill('0') << setw(8) << hex << inst << endl;
		
		// get the bit fields from the instruction
		set_bitfields(inst);

		if (m_opcode == 0x00) 
		{
			instType = 'R';
			this->executeInst_R();
		}

		else if (m_opcode == 0x02 || m_opcode == 0x03)
		{
			instType = 'J';
			this->executeInst_J();
		}

		else 
		{
			instType = 'I';
			this->executeInst_I();
		}
		
		// execution complete. increment PC
		set_pc(PC+4);
		
		if (setBranch && b_count > 0)
		{
			if (jumpLink) 
			{
				Reg[31] = savedAddress + 8;
				jumpLink = false;
			}
			set_pc(branchAddr);
			setBranch = false;			
			b_count = 0;
		}
		n_count++;
  		m_instructioncount++;
	}
	return;
}

void processor::set_bitfields(uint32_t inst)
{
	uint32_t opMask = 0xfc000000;
	uint32_t rsMask = 0x03e00000;
	uint32_t rtMask = 0x001f0000;
	uint32_t rdMask = 0x0000f800;
	uint32_t shamntMask = 0x000007c0;
	uint32_t functMask = 0x0000003f;
	uint32_t immediateMask = 0x0000FFFF;
	uint32_t addressMask = 0x03FFFFFF;	

	m_opcode = (inst & opMask) >> 26;
	m_rs = (inst & rsMask) >> 21;
	m_rt = (inst & rtMask) >> 16;
	m_rd = (inst & rdMask) >> 11;
	m_shamnt = (inst & shamntMask) >> 6;
	m_funct = (inst & functMask);
	m_immediate = (inst & immediateMask);
	m_address = (inst & addressMask);

	return;
} 

// Clear breakpoint
void processor::clear_breakpoint() 
{
	breakpoint = 0;		// we cant clear it. There is always going to be some 32 bit value here that PC could happen to equal
	breakpoint_set = false;

	return;
}

// Set breakpoint at an address
void processor::set_breakpoint(uint32_t address)
{
	if (m_verbose)
		cout << "Breakpoint set at " << setfill('0') << setw(8) << hex << address << endl;
	breakpoint_set = true;
	breakpoint = address;

	return;
}

  // Probe the instruction cache interface for an address
void processor::probe_instruction (uint32_t address) 
{
	if (m_verbose) cout << "CPU: probe instruction address = " << hex << setfill('0') << setw(8) << address << endl;
	// Check icache
	m_icache->probe_address(address);
	return;
}

  // Probe the data cache interface for an address
void processor::probe_data (uint32_t address)
{
	if (m_verbose) cout << "CPU: probe data address = " << hex << setfill('0') << setw(8) << address << endl;
	// Check dcache
	m_dcache->probe_address(address);
	return;
}

uint64_t processor::get_instruction_count() 
{
	return m_instructioncount;
}

uint64_t processor::get_cycle_count()
{
	// not needed for UG
	uint64_t temp = 0;
	return temp; 
}

void processor::executeInst_J()
{
	if (m_opcode == 0x02)
	{
		instType = 'J';
		instMnemonic = "j";
		if (m_verbose) cout << instMnemonic << ": addr = " << hex << setfill('0') << setw(8) << m_address << endl;
		setBranch = true;
		uint32_t addr = (PC & 0xf0000000) | (m_address << 2);
		branchAddr = addr;
		return;
	}
	
	else if (m_opcode == 0x03)
	{
		instType = 'J';
		instMnemonic = "jal";
		if (m_verbose) cout << instMnemonic << " : addr = " << hex << setfill('0') << setw(8) << m_address << endl;
		setBranch = true;
		jumpLink = true;
		savedAddress = PC;
		uint32_t addr = (PC & 0xf0000000) | (m_address << 2);
		branchAddr = addr;
		return;
	}
	cout << "INVALID J INSTRUCTION?" << endl;
	return;
} 

void processor::executeInst_I()
{
	if (m_opcode == 0x20 || m_opcode == 0x21 || m_opcode == 0x24 || m_opcode == 0x25 || m_opcode == 0x28 || m_opcode == 0x29) 
	{
		int addedOffset = 0;
		int wordOffset = 0;
		
		// align address and add that many bytes to align it to our offset
		if (Reg[m_rs] % 4 != 0)
		{
			addedOffset = 0;
			uint32_t wordAddress = Reg[m_rs];
			while (wordAddress % 4 != 0) 
			{
				wordAddress = wordAddress -1;
				addedOffset++;
			}
		}

		int16_t s_imm = m_immediate;	
		int trueOffset = addedOffset + s_imm;

		if (trueOffset >= 0)
			wordOffset = trueOffset/4;
		else
			wordOffset = (trueOffset/4) - 1;

		// get the word we want to focus on
		bool saveVerbose = m_verbose;
		m_verbose = false;
		uint32_t word = m_dcache->read_word(Reg[m_rs] + (4*wordOffset));
		m_verbose = saveVerbose;

		// what is the offset relative to this word?
		// remove the sign if there is one, relative to a base now
		unsigned int newOffset = trueOffset;	
		// minus the amount of words we already moved closer		
		newOffset = trueOffset - (wordOffset * 4);		
		
		switch (newOffset)
		{
			case 0:
			{
				if (m_opcode == 0x20)
				{
					instMnemonic = "lb";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0xFF000000;
					int32_t byte = mask & word;
					byte = byte >> 24;
					int8_t byte2 = byte;
					int32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x21)
				{
					instMnemonic = "lh";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0xFFFF0000;
					int32_t byte = mask & word;
					byte = byte >> 16;
					int16_t byte2 = byte;
					int32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x24)
				{
					instMnemonic = "lbu";
					if (m_verbose) cout << instMnemonic << ": rt = " << dec << m_rt << ", rs = " << m_rs << ", imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0xFF000000;
					int32_t byte = mask & word;
					byte = byte >> 24;
					uint8_t byte2 = byte;
					uint32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x25)
				{
					instMnemonic = "lhu";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0xFFFF0000;
					int32_t byte = mask & word;
					byte = byte >> 16;
					uint16_t byte2 = byte;
					uint32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x28)
				{
					instMnemonic = "sb";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t t_mask = 0x000000FF;
					uint32_t tMasked = Reg[m_rt] & t_mask;
					uint32_t origDataMask = 0x00FFFFFF & word;
					uint32_t newWord = origDataMask | (tMasked << 24);
					m_dcache->write_word(Reg[m_rs] + (4*wordOffset), newWord, 0xFFFFFFFF);
					return;
				}
				else if (m_opcode == 0x29)
				{
					instMnemonic = "sh";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t t_mask = 0x0000FFFF;
					uint32_t tMasked = Reg[m_rt] & t_mask;
					uint32_t origDataMask = 0x0000FFFF & word;
					uint32_t newWord = origDataMask | (tMasked << 16);
					m_dcache->write_word(Reg[m_rs] + (4*wordOffset), newWord, 0xFFFFFFFF);
					return;
				}
				break;
			}
			case 1:
			{
				if (m_opcode == 0x20)
				{
					instMnemonic = "lb";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x00FF0000;
					int32_t byte = mask & word;
					byte = byte >> 16;
					int8_t byte2 = byte;
					int32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x21)
				{
					instMnemonic = "lh";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x00FFFF00;
					int32_t byte = mask & word;
					byte = byte >> 8;
					int16_t byte2 = byte;
					int32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x24)
				{
					instMnemonic = "lbu";
					if (m_verbose) cout << instMnemonic << ": rt = " << dec << m_rt << ", rs = " << m_rs << ", imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x00FF0000;
					int32_t byte = mask & word;
					byte = byte >> 16;
					uint8_t byte2 = byte;
					uint32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x25)
				{
					instMnemonic = "lhu";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x00FFFF00;
					int32_t byte = mask & word;
					byte = byte >> 8;
					uint16_t byte2 = byte;
					uint32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x28)
				{
					instMnemonic = "sb";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t t_mask = 0x000000FF;
					uint32_t tMasked = Reg[m_rt] & t_mask;
					uint32_t origDataMask = 0xFF00FFFF & word;
					uint32_t newWord = origDataMask | (tMasked << 16);
					m_dcache->write_word(Reg[m_rs] + (4*wordOffset), newWord, 0xFFFFFFFF);
					return;
				}
				else if (m_opcode == 0x29)
				{
					instMnemonic = "sh";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t t_mask = 0x0000FFFF;
					uint32_t tMasked = Reg[m_rt] & t_mask;
					uint32_t origDataMask = 0xFF0000FF & word;
					uint32_t newWord = origDataMask | (tMasked << 8);
					m_dcache->write_word(Reg[m_rs] + (4*wordOffset), newWord, 0xFFFFFFFF);
					return;
				}
				break;
			}
			case 2:
			{
				if (m_opcode == 0x20)
				{
					instMnemonic = "lb";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x0000FF00;
					int32_t byte = mask & word;
					byte = byte >> 8;
					int8_t byte2 = byte;
					int32_t byte_ext = byte2;		
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x21)
				{
					instMnemonic = "lh";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x0000FFFF;
					int32_t byte = mask & word;
					byte = byte >> 0;
					int16_t byte2 = byte;
					int32_t byte_ext = byte2;		
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x24)
				{
					instMnemonic = "lbu";
					if (m_verbose) cout << instMnemonic << ": rt = " << dec << m_rt << ", rs = " << m_rs << ", imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x0000FF00;
					int32_t byte = mask & word;
					byte = byte >> 8;
					uint8_t byte2 = byte;
					uint32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x25)
				{
					instMnemonic = "lhu";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x0000FFFF;
					int32_t byte = mask & word;
					byte = byte >> 0;
					uint16_t byte2 = byte;
					uint32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x28)
				{
					instMnemonic = "sb";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t t_mask = 0x000000FF;
					uint32_t tMasked = Reg[m_rt] & t_mask;
					uint32_t origDataMask = 0xFFFF00FF & word;
					uint32_t newWord = origDataMask | (tMasked << 8);
					m_dcache->write_word(Reg[m_rs] + (4*wordOffset), newWord, 0xFFFFFFFF);
					return;
				}
				else if (m_opcode == 0x29)
				{
					instMnemonic = "sh";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t t_mask = 0x0000FFFF;
					uint32_t tMasked = Reg[m_rt] & t_mask;
					uint32_t origDataMask = 0xFFFF0000 & word;
					uint32_t newWord = origDataMask | tMasked;
					m_dcache->write_word(Reg[m_rs] + (4*wordOffset), newWord, 0xFFFFFFFF);
					return;
				}
				break;
			}
			case 3:
			{
				if (m_opcode == 0x20)
				{
					instMnemonic = "lb";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x000000FF;
					int32_t byte = mask & word;
					byte = byte >> 0;
					int8_t byte2 = byte;
					int32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x24)
				{
					instMnemonic = "lbu";
					if (m_verbose) cout << instMnemonic << ": rt = " << dec << m_rt << ", rs = " << m_rs << ", imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t mask = 0x000000FF;
					int32_t byte = mask & word;
					byte = byte >> 0;
					uint8_t byte2 = byte;
					uint32_t byte_ext = byte2;
					Reg[m_rt] = byte_ext;
					return;
				}
				else if (m_opcode == 0x28)
				{
					instMnemonic = "sb";
					
					if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
					uint32_t t_mask = 0x000000FF;
					uint32_t tMasked = Reg[m_rt] & t_mask;
					uint32_t origDataMask = 0xFFFFFF00 & word;
					uint32_t newWord = origDataMask | tMasked;
					m_dcache->write_word(Reg[m_rs] + (4*wordOffset), newWord, 0xFFFFFFFF);
					return;
				}
				break;
			}
			default:
			{
				cout << "Fatal Error: Offset at this stage should be between 0 and 3 bytes relative to a word base address." << endl;
				return;
			}
		}
	}
	else if  (m_opcode == 0x23)
	{
		instMnemonic = "lw";
		
		int16_t s_imm = m_immediate;
		if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
		if (m_rt != 0) Reg[m_rt] = m_dcache->read_word(Reg[m_rs] + s_imm);
		return;
	}
	else if (m_opcode == 0x2B)
	{
		instMnemonic = "sw";
		
		int16_t s_imm = m_immediate;
		if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
		//cout << "WE WANT TO STORE THE WORD: " << hex << setfill('0') << setw(8) << Reg[m_rt] << ", AT ADDRESS: " << hex << setfill('0') << setw(8) << Reg[m_rs] + s_imm << endl;
		m_dcache->write_word(Reg[m_rs] + s_imm, Reg[m_rt], 0xFFFFFFFF);
		return;
	}
	else if (m_opcode == 0x08)
	{
		instMnemonic = "addi";
		int16_t temp = m_immediate;
		// sign extend
		int32_t imm_32s = temp;
		int32_t rs_s = Reg[m_rs];
		if (m_verbose) cout << instMnemonic << ": rt = " << dec << m_rt << ", rs = " << dec << m_rs << ", imm = " << hex << setfill('0') << setw(8) << imm_32s << endl;
		if (m_rt != 0) Reg[m_rt] = rs_s + imm_32s;
		return;
	}
	else if (m_opcode == 0x09)
	{
		instMnemonic = "addiu";
		int16_t temp = m_immediate;
		// sign extend
		int32_t imm_32s = temp;
		if (m_verbose) cout << instMnemonic << ": rt = " << dec << m_rt << ", rs = " << dec << m_rs << ", imm = " << hex << setfill('0') << setw(8) << imm_32s << endl;
		if (m_rt != 0) Reg[m_rt] = Reg[m_rs] + imm_32s;
		return;
	}
	else if (m_opcode == 0x0A)
	{
		instMnemonic = "slti";
		
		// sign extend m_immediate
		int16_t temp = m_immediate;
		int32_t s_imm = temp;
		if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << s_imm << endl;
		if (m_rt != 0)
		{
			int32_t s_rs = Reg[m_rs];
			if (s_rs < s_imm)
				Reg[m_rt] = 1;
			else 
				Reg[m_rt] = 0;
		}
		return;
	}
	else if (m_opcode == 0x0B)
	{
		instMnemonic = "sltiu";
		

		// sign extend m_immediate
		int16_t temp = m_immediate;
		int32_t temp2 = temp;
		uint32_t u32_imm = temp2;
		if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << u32_imm << endl;

		if (m_rt != 0)
		{
			if (Reg[m_rs] < u32_imm)
				Reg[m_rt] = 1;
			else
				Reg[m_rt] = 0;
		}
		return;
	}
	else if (m_opcode == 0x0C)
	{
		instMnemonic = "andi";;
		uint32_t ext_imm = m_immediate;
		if (m_verbose) cout << instMnemonic << ": rt = " << dec << m_rt << ", rs = " << dec << m_rs << ", imm = " << hex << setfill('0') << setw(8) << ext_imm << endl;
		if (m_rt != 0)
		{
			Reg[m_rt] = Reg[m_rs] & ext_imm;
		}
		return;
	}
	else if (m_opcode == 0x0D) 
	{
		instMnemonic = "ori";
		
		uint32_t ext_imm = m_immediate;
		if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << ext_imm << endl;
		if (m_rt != 0)
		{
			Reg[m_rt] = Reg[m_rs] | ext_imm;
		}
		return;
	}
	else if (m_opcode == 0x0E) 
	{
		instMnemonic = "xori";
		
		uint32_t ext_imm = m_immediate;
		if (m_verbose) cout << "imm = " << hex << setfill('0') << setw(8) << ext_imm << endl;
		if (m_rt != 0)
		{
			Reg[m_rt] = Reg[m_rs] ^ ext_imm;
		}
		return;
	}	
	else if (m_opcode == 0x0F)
	{
		instMnemonic = "lui";
		if (m_verbose) cout << instMnemonic << ": rt = " << dec << m_rt << ", imm = " << hex << setfill('0') << setw(8) << m_immediate << endl;
		uint32_t temp = m_immediate << 16;
		Reg[m_rt] = temp;
		return;
	}
	else if (m_opcode == 0x01 && m_rt == 1)
	{
		instMnemonic = "bgez";
		int16_t s16_imm = m_immediate;
		int32_t s32_imm = s16_imm;
		if (m_verbose) cout << instMnemonic << ": rs = " << dec << m_rs << ", imm = " << hex << setfill('0') << setw(8) << s32_imm << endl;
		s32_imm = s32_imm << 2;
		int32_t signed_rs = Reg[m_rs];
		if (signed_rs >= 0)
		{
			setBranch = true;
			branchAddr = ((PC+4) + s32_imm);
		}
		return;
	}	
	else if (m_opcode == 0x01 && m_rt == 0)
	{
		instMnemonic = "bltz";
		
		int16_t s16_imm = m_immediate;
		int32_t s32_imm = s16_imm;	
		if (m_verbose) cout << instMnemonic << ": rs = " << dec << m_rs << ", imm = " << hex << setfill('0') << setw(8) << s32_imm << endl;
		s32_imm = s32_imm << 2;
		int32_t signed_rs = Reg[m_rs];
		if (signed_rs < 0)
		{
			setBranch = true;
			branchAddr = ((PC+4) + s32_imm);
		}
		return;
	}
	else if (m_opcode == 0x04)
	{
		instMnemonic = "beq";
		int16_t s16_imm = m_immediate;
		int32_t s32_imm = s16_imm;	
		if (m_verbose) cout << instMnemonic << ": rs = " << dec << m_rs << ", rt = " << dec << m_rt << ", imm = " << hex << setfill('0') << setw(8) << s32_imm << endl;
		s32_imm = s32_imm << 2;
		if (Reg[m_rs] == Reg[m_rt])
		{
			setBranch = true;
			branchAddr = ((PC+4) + s32_imm);
		}
		return;
	}
	else if (m_opcode == 0x05)
	{
		instMnemonic = "bne";
		int16_t s16_imm = m_immediate;
		int32_t s32_imm = s16_imm;
		if (m_verbose) cout << instMnemonic << ": rs = " << dec << m_rs << ", rt = " << dec << m_rt << ", imm = " << hex << setfill('0') << setw(8) << s32_imm << endl;
		s32_imm = s32_imm << 2;
		if (Reg[m_rs] != Reg[m_rt])
		{
			setBranch = true;
			branchAddr = ((PC+4) + s32_imm);
		}
		return;
	}
	else if (m_opcode == 0x06)
	{
		instMnemonic = "blez";
		
		int16_t s16_imm = m_immediate;
		int32_t s32_imm = s16_imm;	
		if (m_verbose) cout << instMnemonic << ": rs = " << dec << m_rs << ", imm = " << hex << setfill('0') << setw(8) << s32_imm << endl;
		s32_imm = s32_imm << 2;
		int32_t signed_rs = Reg[m_rs];
		if (signed_rs <= 0)
		{
			setBranch = true;
			branchAddr = ((PC+4) + s32_imm);
		}
		return;
	}
	else if (m_opcode == 0x07)
	{
		instMnemonic = "bgtz";
		
		int16_t s16_imm = m_immediate;
		int32_t s32_imm = s16_imm;	
		if (m_verbose) cout << instMnemonic << ": rs = " << dec << m_rs << ", imm = " << hex << setfill('0') << setw(8) << s32_imm << endl;
		s32_imm = s32_imm << 2;
		int32_t signed_rs = Reg[m_rs];
		if (signed_rs > 0)
		{
			setBranch = true;
			branchAddr = ((PC+4) + s32_imm);
		}
		return;
	}
	cout << "INVALID I INSTRUCTION?" << endl;
	return;
}

void processor::executeInst_R()
{
	if (m_funct == 0x00)
	{
		instMnemonic = "sll";
		if (m_verbose) cout << instMnemonic << ": rd = " << dec << m_rd << ", rt = " << dec << m_rt << ", sa = " << dec << m_shamnt << endl;
		if (m_rd != 0) Reg[m_rd] = Reg[m_rt] << m_shamnt;
		return;
	}
	else if (m_funct == 0x02)
	{
		instMnemonic = "srl";
		
		if (m_rd != 0) Reg[m_rd] = Reg[m_rt] >> m_shamnt;
		return;
	}
	else if (m_funct == 0x03)
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
		return;
	}
	else if (m_funct == 0x08)
	{
		instMnemonic = "jr";
		if (m_verbose) cout << instMnemonic << ": rs = " << dec << m_rs << endl;
		setBranch = true;
		branchAddr = Reg[m_rs];
		return;
	}
	else if (m_funct == 0x09)
	{
		instMnemonic = "jalr";
		if (m_verbose) cout << instMnemonic << ": rs = " << dec << m_rs << endl;
		setBranch = true;
		jumpLink = true;
		savedAddress = PC;
		branchAddr = Reg[m_rs];
		return;
	}
	else if (m_funct == 0x20)
	{
		instMnemonic = "add";
		if (m_verbose) cout << instMnemonic << ": rd = " << dec << m_rd << ", rs = " << dec << m_rs << ", rt = " << dec << m_rt << endl;
		int32_t ts_rs = Reg[m_rs];
		int32_t ts_rt = Reg[m_rt];
		int32_t ts_result = ts_rs + ts_rt;
		if (m_rd != 0) Reg[m_rd] = ts_result;
		return;
	}

	else if (m_funct == 0x21)
	{
		instMnemonic = "addu";
		if (m_verbose) cout << instMnemonic << ": rd = " << dec << m_rd << ", rs = " << dec << m_rs << ", rt = " << dec << m_rt << endl;
		if (m_rd != 0) Reg[m_rd] = Reg[m_rs] + Reg[m_rt];
		return;
	}
	else if (m_funct == 0x22)
	{
		instMnemonic = "sub";
		
		int32_t ts_rs = Reg[m_rs];
		int32_t ts_rt = Reg[m_rt];
		int32_t ts_result = ts_rs - ts_rt;
		if (m_rd != 0) Reg[m_rd] = ts_result;
		return;
	}
	else if (m_funct == 0x23)
	{
		instMnemonic = "subu";
		
		if (m_rd != 0) 
		{
			Reg[m_rd] = Reg[m_rs] - Reg[m_rt];
		}
		return;
	}
	else if (m_funct == 0x24)
	{
		instMnemonic = "and";
		if (m_verbose) cout << instMnemonic << ": rd = " << dec << m_rd << ", rs = " << dec << m_rs << ", rt = " << dec << m_rt << endl;		
		if (m_rd != 0) Reg[m_rd] = Reg[m_rs] & Reg[m_rt];
		return;
	}
	else if (m_funct == 0x25) 
	{
		instMnemonic = "or";
		
		if (m_rd != 0) Reg[m_rd] = Reg[m_rs] | Reg[m_rt];
		return;
	}
	else if (m_funct == 0x26)
	{
		instMnemonic = "xor";
		
		if (m_rd != 0) Reg[m_rd] = Reg[m_rs] ^ Reg[m_rt];
		return;
	}
	else if (m_funct == 0x27)
	{
		instMnemonic = "nor";
		
		if (m_rd != 0) Reg[m_rd] = ~(Reg[m_rs] | Reg[m_rt]);
		return;
	}
	else if (m_funct == 0x2A)
	{
		instMnemonic = "slt";
		
		int32_t ts_rs = Reg[m_rs];
		int32_t ts_rt = Reg[m_rt];
		if (ts_rs < ts_rt)
		{
			if (m_rd != 0)
				Reg[m_rd] = 1;
		}
		else Reg[m_rd] = 0;
		return;
	}
	else if (m_funct == 0x2B)
	{
		instMnemonic = "sltu";
		
		if (Reg[m_rs] < Reg[m_rt])
		{
			if (m_rd != 0)
				Reg[m_rd] = 1;
		}
		else Reg[m_rd] = 0;
		return;
	}
	cout << "INVALID R INSTRUCTION?" << endl;
	return;
}
