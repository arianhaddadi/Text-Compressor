# Deflate_Caesar Encryption and Cipher
This project is an implementation of [Deflate](https://en.wikipedia.org/wiki/Deflate#Encoder/compressor) 
(i.e., [LZ77](https://en.wikipedia.org/wiki/LZ77_and_LZ78) and [Huffman Coding](https://en.wikipedia.org/wiki/Huffman_coding)) and 
[Caesar Cipher](https://en.wikipedia.org/wiki/Caesar_cipher) algorithms for text input files. 

## How to run
This is a CMake project. The executable file after building the project is named `deflate_caesar`.

## Operations

### Codec
You can compress and decompress text input files with [Deflate](https://en.wikipedia.org/wiki/Deflate#Encoder/compressor) with this project.
This algorithm uses [LZ77](https://en.wikipedia.org/wiki/LZ77_and_LZ78) and [Huffman Coding](https://en.wikipedia.org/wiki/Huffman_coding) algorithms respectively and produces a smaller size output file which can be recovered later.

The commands for these operations are:

    deflate_caesar compress <input file> <output file>

and

    deflate_caesar decompress <input file> <output file>


An example would be:

    deflate_caesar compress input.txt out_compress.txt

    deflate_caesar decompress out_compress.txt out_decompress.txt

and the contents of `input.txt` and `out_decompress.txt` files would be the same.

### Encryption/Decryption
You can encrypt and decrypt text input files with [Caesar Cipher](https://en.wikipedia.org/wiki/Caesar_cipher) with this project.

The commands for these operations are:

    deflate_caesar encrypt <input file> <output file> <kNum>

and

    deflate_caesar decrypt <input file> <output file> <kNum>

which `<knum>` is the offset number that all characters would get shifted as much
(e.g., if the characters is `a` and `kNum` is `1`, the resulting character would be `b`, whose ASCII Code is `kNum` more).

An example would be:

    deflate_caesar encrypt input.txt out_encrypt.txt 4

    deflate_caesar decrypt out_encrypt.txt out_decrypt.txt 4

and the contents of `input.txt` and `out_decrypt.txt` files would be the same.

### Codec & Encryption/Decryption
You can combine the above operations as well. This time the text file would get compressed first, and get encrypted afterward.  
The commands for these operations are:

    deflate_caesar compress_encrypt <input file> <output file> <kNum>

and

    deflate_caesar decrypt_decompress <input file> <output file> <kNum>

An example would be:

    deflate_caesar compress_encrypt input.txt out_coenc.txt 4

    deflate_caesar decrypt_decompress out_coenc.txt out_decdec.txt 4

and the contents of `input.txt` and `out_decdec.txt` files would be the same.
