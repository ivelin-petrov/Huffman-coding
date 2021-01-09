# Huffman-coding
A Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. This program initializes the Huffman coding algorithm.

This program uses 'doctest.h' for test cases.

The program simply opens and reads from an existing file, compresses a text and transfers it into another file (or the same one) including the additional data needed 
for the decompression and the compressed text itself. 
The decompression similarly requires an already existing file name (correctly formatted), reads the data on line 1 in the input file, constructs the Huffman Tree containing the 
encoded symbols and decompresses the compressed text on line 2 from the input file into an output file (can be the same as the input).
There is an option for visual representation of the outcome of the compression and decompression feature of the Huffman coding algorithm on an input text in the console.
