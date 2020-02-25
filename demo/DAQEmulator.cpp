#include "DAQEmulator.h"

DAQEmulator::DAQEmulator() {

}

const uint32_t* DAQEmulator::receive_data() {
    return 0;
}

bool DAQEmulator::send_classification(const uint32_t* classification) {
    return true;
}

bool DAQEmulator::start() {

    return true;
}

bool DAQEmulator::stop() {

    return true;
}

bool DAQEmulator::is_stopped() {

    return false;
}
