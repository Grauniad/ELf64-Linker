#ifndef SYMBOL_H
   #define SYMBOL_H
#include "flags.h"
#include "elf.h"
class BinaryReader;

class Symbol {
public:
    Symbol ( const BinaryReader& reader, 
             const BinaryReader& stable );
    size_t Size() { return sizeof(Elf64_Sym); }
    Elf64_Addr& Value() { return symbol.st_value; }
    uint16_t& SegmentIdx() { return symbol.st_shndx; }
    bool IsLinkSymbol();
    void UpdateFlags();
    string LinkFormat();

private:
    void ConfigureFlags();
    Elf64_Sym symbol;
    string name;
    Flags type;
    Flags scope;
};
#endif