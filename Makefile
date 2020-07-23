

TARGET = test.elf

BUILD = build

INCLUDE = header kernel/h

FOLDER_CFILE_COM = source
FOLDER_CFILE_LX = kernel/s_linux

CFILE_TEST = test/hl.test.strf.c

CFILE_COM = \
 hl.startup.c\
 hl.system.memory.c\
 hl.chars.c\
 hl.chars.format.c\
 hl.chars.format.int.c\
 hl.chars.format.text.c\
 hl.chars.format.va.c\
 hl.string.c\
 hl.string.format.c\
 hl.io.path.c\
 hl.io.fileinfo.c\
 hl.io.file.c\
 hl.io.filestream.writer.c\
 hl.io.filestream.reader.c\
 hl.io.textstream.writer.c\
 hl.io.console.c


CFILE_LX = hl.linux.memory.c hl.linux.io.c

ASMFILE_LX = hl.linux.syscall.s


CC = gcc
CFLAGS = -Wall -g -nostdlib -static
SFLAGS = -Wall -g
LFLAGS = $(CFLAGS)
MDFAGS = -MMD -MP -MF $*.d $(CFLAGS)


ARG_INCLUDE = $(foreach dir,$(INCLUDE),-I$(dir))

CFILES = $(CFILE_TEST) \
	$(foreach dir,$(CFILE_COM),$(FOLDER_CFILE_COM)/$(dir)) \
	$(foreach dir,$(CFILE_LX),$(FOLDER_CFILE_LX)/$(dir)) \
	

ASMFILES = $(foreach dir,$(ASMFILE_LX),$(FOLDER_CFILE_LX)/$(dir))

#OFILES = $(patsubst %c, %o, $(foreach dir,$(CFILE_COM),$(CURDIR)/$(BUILD)/$(dir)))\
	$(patsubst %c, %o, $(foreach dir,$(CFILE_LX),$(CURDIR)/$(BUILD)/$(dir)))\
	$(patsubst %c, %o, $(foreach dir,$(ASMFILE_LX),$(CURDIR)/$(BUILD)/$(dir)))

OFILES = $(patsubst %c, %o, $(CFILES)) $(patsubst %s, %o, $(ASMFILES))


%.o: %.c
	@echo $(notdir $<)
	@$(CC) $(CFLAGS) $(ARG_INCLUDE) -c $< -o $@
#@$(CC) -c -g -Wa,-adlhn $(ARG_INCLUDE) -masm=intel $< > $(patsubst %.o, %.s, $@)


%.o: %.s
	@echo $(notdir $<)
	@$(CC) $(SFLAGS) -c $< -o $@


$(TARGET): $(OFILES)
	@$(CC) $(LFLAGS) $(OFILES) -o $(TARGET)
	@rm -fr -v $(OFILES)
	@echo ==== Compile Success ====

#@echo ==== Running: $(TARGET) =====
#@./$(TARGET)

clean:
	@rm -fr -v $(OFILES)
	@rm -fr -v $(TARGET)
#@rm -fr -v $(patsubst %c, %s, $(CFILES))
#@rm -fr -v $(patsubst %o, %d, $(OFILES))



