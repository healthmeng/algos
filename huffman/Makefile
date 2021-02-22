huff:huffman.c huffman.h
	gcc huffman.c -o huff -g -O0

bits.o:bits.c bits.h
	gcc -c bits.c -g -O0

test:bits.o test.o
	gcc -o test bits.o test.o

test.o:test.c bits.h
	gcc -c -g -O0 test.c

clean:
	rm -f huff test *.o

