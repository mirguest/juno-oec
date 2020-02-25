#ifndef OECController_h
#define OECController_h

#include <stdint.h>

class OECController {
public:
    OECController();

    bool initialize();
    const uint32_t* execute(const uint32_t* buffer);
    bool finalize();
    
};

#endif
