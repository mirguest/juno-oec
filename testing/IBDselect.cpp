#include <iostream>
#include <vector>
#include <map>


enum tECut: unsigned {
    tEless0d75MeV,
    tEless1d60MeV,
    tEless2d60MeV,
    tEless3d50MeV,
    tEless100MeV,
    tEgreat100MeV
};

enum pECut: unsigned {
    pEless100MeV,
    pEgreat100MeV
};

enum distCut: unsigned {
    distless2d5m,
    distgreat2d5m
};

enum timeCut: unsigned {
    timeless10us,
    timegreat10us
};

#define MASK(TE, PE, DI, TI) ((TE<<24) | (PE<<16) | (DI<<8) | (TI))

struct {
    unsigned selection;
    unsigned tag;
} tables[] = {
};

struct IBDselect {

};

int main() {
    IBDselect selalg;


}
