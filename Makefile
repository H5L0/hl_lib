

TARGET = test.elf

INCLUDE = header _kernel/h

FOLDER_CFILE_COM = source
FOLDER_CFILE_LX = _kernel/s_linux


CFILE_COM = \
 hl.startup.c\
 hl.system.memory.c\
 hl.string.c\
 hl.io.path.c\
 hl.io.fileinfo.c\
 hl.io.file.c\
 hl.io.filestream.c\
 main_test02.c


CFILE_LX = hl.linux.memory.c hl.linux.io.c

ASMFILE_LX = hl.linux.syscall.s


CFLAGS = -Wall -g -nostdlib -static


FLAG_INCLUDE = $(foreach dir,$(INCLUDE),-I$(dir))

PATH_CFILE = $(foreach dir,$(CFILE_COM),$(CURDIR)/$(FOLDER_CFILE_COM)/$(dir)) \
	$(foreach dir,$(CFILE_LX),$(CURDIR)/$(FOLDER_CFILE_LX)/$(dir)) \
	$(foreach dir,$(ASMFILE_LX),$(CURDIR)/$(FOLDER_CFILE_LX)/$(dir))



%.c:
	@echo $*

%.s:
	@echo $*


$(TARGET): $(CFILE_COM) $(CFILE_LX) $(ASMFILE_LX)
	@clang $(CFLAGS) -o $(TARGET) $(FLAG_INCLUDE) $(PATH_CFILE)
	@echo ==== Running: $(TARGET) =====
	#@./$(TARGET)


