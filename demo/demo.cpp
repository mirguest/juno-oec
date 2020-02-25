
#include "DAQEmulator.h"
#include "OECController.h"

int main() {
    DAQEmulator* daq_emulator = new DAQEmulator(); // the emulator for OEC

    OECController* oec_controller = new OECController();

    daq_emulator->start();
    oec_controller->initialize();

    // event loop here
    for (;;) {
        if (daq_emulator->is_stopped()) {
            break;
        }

        // DAQ prepare the data for us.
        const uint32_t* buffer = daq_emulator->receive_data();
        // DAQ invoke the oec controller
        const uint32_t* classification = oec_controller->execute(buffer);

        // send the result back
        daq_emulator->send_classification(classification);
    }

    oec_controller->finalize();
    daq_emulator->stop();

}
