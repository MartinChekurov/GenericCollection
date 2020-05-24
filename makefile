build = Build
src = main ArrayList/ArrayList LinkedList/LinkedList
obj = $(addsuffix .o, $(addprefix $(build)/, $(src)))
CFLAGS = -IArrayList -ILinkedList -IList
CC = gcc

all: $(build)/test.exe

$(build)/test.exe: $(obj)
	@echo LINKING $^
	@$(CC) -o $@ $^
	
$(build)/%.o: %.c
	@echo COMPILING $<
	@mkdir -p $(subst /,\,$(dir $@))
	@$(CC) $(CFLAGS) -M -MT $@ -o $(patsubst %.o, %.d, $@) $<
	@$(CC) $(CFLAGS) -o $@ -c $<
	
-include $(obj:.o=.d) 
	
.PHONY: clean

clean:
	@echo CLEANING......
	@@rm -rf $(build)/*