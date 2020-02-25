#ifndef DAQEmulator_h
#define DAQEmulator_h

#include <stdint.h>

class DAQEmulator {
public:

    DAQEmulator();

    const uint32_t* receive_data();
    bool send_classification(const uint32_t* classification);

    bool start();
    bool stop();

    bool is_stopped();

private:
    
};

#endif
