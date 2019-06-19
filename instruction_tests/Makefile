RM=rm -f
AS=mips-mti-elf-as
LD=mips-mti-elf-ld
OBJCOPY=mips-mti-elf-objcopy

SRCS=$(wildcard *.s)
OBJS=$(subst .s,.o,$(SRCS))
LSTS=$(subst .s,.lst,$(SRCS))
ELFS=$(subst .s,.elf,$(SRCS))
HEXS=$(subst .s,.hex,$(SRCS))

%.o: %.s
	$(AS) -o $@ -a=$*.lst $<

%.elf: %.o
	$(LD) -o $@ $<

%.hex: %.elf
	$(OBJCOPY) --output-target ihex $< $@

all: $(HEXS)

clean:
	$(RM) $(OBJS) $(LSTS) $(ELFS) $(HEXS)
