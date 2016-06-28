EXEC=test
OUTPUT=debug
SGI_HEADERS=list stl_algobase.h stl_alloc.h stl_config.h \
						stl_construct.h stl_iterator.h stl_list.h \
						stl_pair.h stl_relops.h stl_uninitialized.h \
						type_traits.h

all: $(OUTPUT) $(EXEC)

$(OUTPUT):
	[ -d $(OUTPUT) ] || mkdir $(OUTPUT)

$(EXEC): test.o
	g++ -o $(OUTPUT)/test $(OUTPUT)/test.o

test.o: test.cc $(SGI_HEADERS)
	g++ -O0 -g3 -Wall -fmessage-length=0 -I. -o $(OUTPUT)/test.o -c test.cc

clean:
	rm -fr $(OUTPUT)
