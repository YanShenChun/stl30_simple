EXEC=test
SGI_HEADERS=list stl_algobase.h stl_alloc.h stl_config.h \
						stl_construct.h stl_iterator.h stl_list.h \
						stl_pair.h stl_relops.h stl_uninitialized.h \
						type_traits.h

$(EXEC): test.o
	g++ -o test test.o

test.o: test.cc $(SGI_HEADERS)
	g++ -g -I. -o test.o -c test.cc

clean:
	rm -f test test.o
