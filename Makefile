EXEC_LIST=test_list
EXEC_VECTOR=test_vector
OUTPUT=debug
SGI_LIST_HEADERS=list stl_algobase.h stl_alloc.h stl_config.h \
						stl_construct.h stl_iterator.h stl_list.h \
						stl_pair.h stl_relops.h stl_uninitialized.h \
						type_traits.h

SGI_VECTOR_HEADERS=vector stl_algobase.h stl_alloc.h stl_config.h \
						stl_construct.h stl_iterator.h stl_vector.h \
						stl_pair.h stl_relops.h stl_uninitialized.h \
						type_traits.h


_list: $(OUTPUT) $(EXEC_LIST)

_vector: $(OUTPUT) $(EXEC_VECTOR)

$(OUTPUT):
	[ -d $(OUTPUT) ] || mkdir $(OUTPUT)

$(EXEC_LIST): $(EXEC_LIST).o
	g++ -o $(OUTPUT)/$(EXEC_LIST) $(OUTPUT)/$(EXEC_LIST).o

$(EXEC_LIST).o: $(EXEC_LIST).cc $(SGI_LIST_HEADERS)
	g++ -O0 -g3 -Wall -fmessage-length=0 -I. -o $(OUTPUT)/$(EXEC_LIST).o -c $(EXEC_LIST).cc

$(EXEC_VECTOR): $(EXEC_VECTOR).o
	g++ -o $(OUTPUT)/$(EXEC_VECTOR) $(OUTPUT)/$(EXEC_VECTOR).o

$(EXEC_VECTOR).o: $(EXEC_VECTOR).cc $(SGI_VECTOR_HEADERS)
	g++ -O0 -g3 -Wall -fmessage-length=0 -I. -o $(OUTPUT)/$(EXEC_VECTOR).o -c $(EXEC_VECTOR).cc


clean:
	rm -fr $(OUTPUT)
