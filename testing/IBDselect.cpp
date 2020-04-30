#include <iostream>
#include <iomanip>
#include <vector>
#include <map>

struct CutRange {
    double low;
    double high;
};

// 8bit
enum tECut: unsigned {
    tEless0d75MeV,
    tEless1d60MeV,
    tEless2d60MeV,
    tEless3d50MeV,
    tEless100MeV,
    tEgreat100MeV,
    tENum, // total number
    tEAny = 0xFF
};

CutRange tEcutRange[] = {
    {0, 0.75},
    {0, 1.6},
    {0, 2.6},
    {0, 3.5},
    {0, 100},
    {100, 0}
};

// 4bit
enum pECut: unsigned {
    pEless100MeV,
    pEgreat100MeV, // this label will cover pEless1GeV and pEgreat1GeV
    pENum, // total number
    pEAny = 0xF
};

CutRange pEcutRange[] = {
    {0, 100},
    {100, 0}
};

// 4bit
enum pE2Cut: unsigned {
    pE2less100MeV,
    pE2less1GeV,
    pE2great1GeV,
    pE2Num, // total number
    pE2Any = 0xF
};

CutRange pE2cutRange[] = {
    {0, 100},
    {0, 1000},
    {1000, 0},
};

// 8bit
enum distCut: unsigned {
    distless2d5m,
    distgreat2d5m,
    distNum,
    distAny = 0xFF
};

CutRange distcutRange[] {
    {0, 2500},
    {2500, 0}
};

// 8bit
enum timeCut: unsigned {
    timeless10us,
    timegreat10us,
    timeNum,
    timeAny = 0xFF
};

CutRange timecutRange[] {
    {0, 10000}, // [0, 10 us]
    {10000, 0}  // [10 us, ...]
};


enum Tag: unsigned {
    tagUnknown,
    tagSpallationNeutron,
    tagCoinc,
    tagIBD,
    tagProtonDecay
};

// #define MASK(TE, PE, DI, TI) ((TE<<24) | (PE<<16) | (DI<<8) | (TI)), (TE), (PE), (DI), (TI)
// #define MASK(TE, PE, PE2, DI, TI) (TE), (PE), (PE2), (DI), (TI)
#define MASK(TE, PE, PE2, DI, TI) (( TE<<24) | \
                                   ( PE<<20) | \
                                   (PE2<<16) | \
                                   ( DI<< 8) | \
                                   ( TI<< 0)),                            \
                                   (TE), (PE), (PE2), (DI), (TI)
struct Pair {
    unsigned int selection;
    enum tECut _tEcut;
    enum pECut _pEcut;
    enum pE2Cut _pE2cut;
    enum distCut _distcut;
    enum timeCut _timecut;
    Tag tag;
} tables[] = {
    // sorted from small to large

    {MASK(tEless0d75MeV, pEAny,         pE2Any, distAny,       timeAny),       tagUnknown},

    {MASK(tEless1d60MeV, pEless100MeV,  pE2Any, distless2d5m,  timeAny),       tagCoinc},
    {MASK(tEless1d60MeV, pEless100MeV,  pE2Any, distgreat2d5m, timeAny),       tagUnknown},
    {MASK(tEless1d60MeV, pEgreat100MeV, pE2Any, distAny,       timeAny),       tagSpallationNeutron},

    {MASK(tEless2d60MeV, pEless100MeV,  pE2Any, distless2d5m,  timeAny),       tagIBD},
    {MASK(tEless2d60MeV, pEless100MeV,  pE2Any, distgreat2d5m, timeAny),       tagUnknown},
    {MASK(tEless2d60MeV, pEgreat100MeV, pE2Any, distAny,       timeAny),       tagSpallationNeutron},

    {MASK(tEless3d50MeV, pEless100MeV,  pE2Any, distless2d5m,  timeAny),       tagCoinc},
    {MASK(tEless3d50MeV, pEless100MeV,  pE2Any, distgreat2d5m, timeAny),       tagUnknown},
    {MASK(tEless3d50MeV, pEgreat100MeV, pE2Any, distAny,       timeAny),       tagSpallationNeutron},

    {MASK(tEless100MeV,  pEAny,  pE2less100MeV, distAny,       timeAny),       tagUnknown},
    {MASK(tEless100MeV,  pEAny,    pE2less1GeV, distAny,       timeless10us),  tagProtonDecay},
    {MASK(tEless100MeV,  pEAny,    pE2less1GeV, distAny,       timegreat10us), tagUnknown},
    {MASK(tEless100MeV,  pEAny,   pE2great1GeV, distAny,       timeAny),       tagUnknown},

    {MASK(tEgreat100MeV, pEAny,         pE2Any, distAny,       timeAny),       tagUnknown},

    {MASK(tEAny,         pEAny,         pE2Any, distAny,       timeAny),       tagUnknown} // the last one
};

struct IBDselect {
    bool initialize() {
        // dump the table

        std::cout << "Initializing the tables. " << std::endl;
        for (Pair* p = tables; p->selection != 0xFFFFFFFF; ++p) {
            std::cout << "0x" << std::setfill('0') << std::setw(8) << std::hex << p->selection << std::endl;
        }
        std::cout << "Initialize the tables done. " << std::endl;

        return true;
    }

    bool execute() {

        // the quick selection flow: 
        // 1) tE (MeV)
        // 2) pE (MeV)
        // 3) dist (mm)
        // 4) time (ns)
        double tE = 2.0;
        double pE = 1.0;
        double dist = 50;
        double time = 10000; // 10 us
        Tag tag = get_tag(tE, pE, dist, time);

        return true;
    }

    Tag get_tag(double tE, double pE, double dist, double time) {

        enum tECut _tEcut = get_tEcut(tE);
        enum pECut _pEcut = get_pEcut(pE);
        enum pE2Cut _pE2cut = get_pE2cut(pE);
        enum distCut _distcut = get_distcut(dist);
        enum timeCut _timecut = get_timecut(dist);

        Tag tag = tagUnknown;

        std::cout << " tE: " << tE
                  << " pE: " << pE
                  << " dist: " << dist
                  << " time: " << time
                  << std::endl;
        std::cout << " tECut: " << _tEcut
                  << " pECut: " << _pEcut
                  << " distCut: " << _distcut
                  << " timeCut: " << _timecut
                  << std::endl;

        

        for (Pair* p = tables; p->selection != 0xFFFFFFFF; ++p) {
            if (p->_tEcut != tEAny && _tEcut != p->_tEcut) {
                continue;
            }

            if (p->_pEcut != pEAny && _pEcut != p->_pEcut) {
                continue;
            }

            if (p->_pE2cut != pE2Any && _pE2cut != p->_pE2cut) {
                continue;
            }

            if (p->_distcut != distAny && _distcut != p->_distcut) {
                continue;
            }

            if (p->_timecut != timeAny && _timecut != p->_timecut) {
                continue;
            }

            // found the tag
            tag = p->tag;

            break;

        }

        std::cout << " found Tag: " << tag << std::endl;

        return tag;
    }

    enum tECut get_tEcut(float tE) {
        enum tECut _tEcut = tEAny;

        for (unsigned int i = 0; i < tENum; ++i) {
            if (tE < tEcutRange[i].low) {
                continue;
            }
            if (tEcutRange[i].high != 0 && tE > tEcutRange[i].high) {
                continue;
            }
            // in the range
            _tEcut = tECut(i);
            break;
        }

        return _tEcut;
    }

    enum pECut get_pEcut(float pE) {
        enum pECut _pEcut = pEAny;

        for (unsigned int i = 0; i < pENum; ++i) {
            if (pE < pEcutRange[i].low) {
                continue;
            }
            if (pEcutRange[i].high != 0 && pE > pEcutRange[i].high) {
                continue;
            }
            // in the range
            _pEcut = pECut(i);
            break;
        }

        return _pEcut;
    }

    enum pE2Cut get_pE2cut(float pE) {
        enum pE2Cut _pE2cut = pE2Any;

        for (unsigned int i = 0; i < pE2Num; ++i) {
            if (pE < pE2cutRange[i].low) {
                continue;
            }
            if (pE2cutRange[i].high != 0 && pE > pE2cutRange[i].high) {
                continue;
            }
            // in the range
            _pE2cut = pE2Cut(i);
            break;
        }

        return _pE2cut;
    }

    enum distCut get_distcut(float dist) {
        enum distCut _distcut = distAny;

        for (unsigned int i = 0; i < distNum; ++i) {
            if (dist < distcutRange[i].low) {
                continue;
            }
            if (distcutRange[i].high != 0 && dist > distcutRange[i].high) {
                continue;
            }
            // in the range
            _distcut = distCut(i);
            break;
        }

        return _distcut;
    }

    enum timeCut get_timecut(float time) {
        enum timeCut _timecut = timeAny;

        for (unsigned int i = 0; i < timeNum; ++i) {
            if (time < timecutRange[i].low) {
                continue;
            }
            if (timecutRange[i].high != 0 && time > timecutRange[i].high) {
                continue;
            }
            // in the range
            _timecut = timeCut(i);
            break;
        }

        return _timecut;
    }

    
};

int main() {
    IBDselect selalg;

    selalg.initialize();
    selalg.execute();
}
