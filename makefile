all: huff test_compress test_decompress test_helpers
huff: main.c compression.c decompression.c io.c helpers.c
	- gcc -g -std=c99 -Wall -Werror main.c compression.c decompression.c helpers.c io.c -o huff
test_decompress: test_decompression.c decompression.c io.c helpers.c
	- gcc -Wall -Werror test_decompression.c decompression.c helpers.c io.c -o test_decompress
test_helpers: test_helpers.c io.c helpers.c
	- gcc -Wall -Werror test_helpers.c helpers.c io.c -o test_helpers
test_compress: test_compression.c compression.c io.c helpers.c
	- gcc -Wall test_compression.c compression.c helpers.c io.c -o test_compress
