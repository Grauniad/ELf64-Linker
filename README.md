Given the messy nature of dealing with "real" object files it has been necessary to expand the format definition from the book. Changes are listed here:

Symbols:
Some convention for empty symbol names is required. "__blank__" has been chosen

The file header has an extra field, flags,  which tells the linker how to handle the file. Flags
     2: Negative numbers are represented as a 2's compliment of a number
     L: addresses are little endian
     B: addresses are big endian

The symbol definition has an extra flag: "scope" tacked on to the end:
     G: Global
     L: Local 

In the books definition a symbol has two types, D and U, but the other types returned by readelf seem like they could be useful. Here is the current map from readelf to LINK (note: "D" has been abandoned, and is instead implied by a lack of "U"):
     U: NOTYPE
     F: FILE 
     S: SECTION
     O: OBJECT
     P: FUNC (mnemonic: PROC)
     


Section  Headers:
An alignment value (int) has been tacked on to the end of the section header. Value is in bytes

There are now a whole bunch of extra flags. Here is the mapping from objdump to LINK:
     P: CONTENTS
     R: READABLE
     W: WRITEABLE (objdump has a read-only flag, the absensce of which is treated as a W flag)
     M: RELOC
     D: DATA
     C: CODE

Program Headers:
Elf distinguishes between section and program blocks. Sections are used by linkers / debuggers to fiddle with the object file. Program headers tell the Kernel what bits of of the file to load into memorry.

So, all the code sections for an object file will be in consecutive blocks of memory and a single program header directs the Kernel to load it as a segment into memory.

Format
addr size(file) size(mem) align type flags 

addr: Hex (virtual) address data is to be loaded into
size: Hex size of the image in memory, and in the file. 
align: data will be paded to this boundrary
flags: Executable: E, Readable: R, Writeable: W
type:  Load: L, Dynamic Loading: D, Note (comment): N, 

For more information see the elf.h man page...
Relocation:

whie the output of readelf and the huge output table in [1] are somewhat intimidating, it seems like this mess of information can actually be reduced right down. 

loc seg ref type x86_type add 

loc: HEX offset within the segment seg to place the result
seg: section to place the result
ref: Where to find the input data. Depending on type this either a section index (Name) or symbol (name)
type: How to handle this relocation entry, see below
x86_type: Type of relocation readelf reports this as. This is ignored by the linker, but may be used by link2elf to recover type information
add: Addendum to add to the value of symbol( Signed Hex)

type flags:

A: Absolute Reference
R: Relative Reference
S: ref is a symbol (by default ref is a segment NAME)
1: size of the value to relocate is 1 bytes
2: size of the value to relocate is 2 bytes
4: size of the value to relocate is 4 bytes
8: size of the value to relocate is 8 bytes
+: There is an addendum for this reloc entry (more specifically this was extracted from a .rela section)
Z: This address will be zero extended when loaded into a register (linker must behave appropriately)
I: This will be sign extended (this sign bit will be used to determine the fill) when this address is loaded into a register


(U and L are currently not generated by els2link)

WARNING: the addendum convetion has changed from the book. In the book addendum values are retrieved from the location. Since the elf data structures (man elf) explicity define a field in the relcoation entry for the addendum value, and readelf reports it in place - the covention has been changed to read it directly out of the reloc entry, with the value at loc considered to be a filler value
Types: 


I found the links below useful, particuarly the abi reference for x8 linked of [2] , but until you throw a few objdump / nm commands around its a all a load of hocus pocus...

=== Trunctation in X8 ===

Most of the instructions available don't actually accept 64 bit arguments. Depending on the size of your binary (i.e whether you actually need 64 bit pointers or not) the compiler is free to choose an addressing convention the speeds things  up by making use of operations that only take 32 bit operands. This does however mean we have to get nightmarishly close to the ABI when writing a linker.


=== Small Code Model ==

To use this model the virtual address of all code most be known in runtime (i.e we can't generate PIC code).

We are only allowed to use 32 bit pointers - so we can only address 2G

[1] For more information than you could ever reasonably want to know abouy the elf format: (its not short - bring a cup of coffee): http://www.acsu.buffalo.edu/~charngda/elf.html

[2] A discussion on calculating the values of relocations: http://www.mindfruit.co.uk/2012/06/interpreting-readelf-r-in-this-case.html 
