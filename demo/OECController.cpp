#include <iostream>

#include "OECController.h"
#include "DataHelper.h"

#include "OECTypes.h"
#include "OECStep.h"

OECController::OECController() {

}

bool OECController::initialize() {

    std::cout << "sizeof(Event)"
              << sizeof(Event) << std::endl;

    // initializing

    return true;
}

const uint32_t* OECController::execute(const uint32_t* buffer) {

    Event event;
    DataDecoding::decode(buffer, event);

    while (OECStep* step = next()) {
        // more calculation
        step->dostep();
        // decision: get the OECTag
        OECTag tag = Unknown;
    }

    return 0;
}

bool OECController::finalize() {
    return true;
}
