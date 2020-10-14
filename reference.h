#pragma once
#include <cstddef>
#include <cstdint>
enum Nucl
{
    A, G, C, U
};

class RNA;

class Reference
{
private:
    size_t rind;
    RNA* rrna;
public:
    size_t cross=sizeof(size_t)/2*8;


    Reference(RNA* rna,size_t ind);
    Reference& operator=(Nucl nucl);
    Reference& operator=(const Reference);
    //Reference& operator=(Nucl);
};
