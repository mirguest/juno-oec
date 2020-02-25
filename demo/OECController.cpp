#include <iostream>

#include "OECController.h"
#include "DataHelper.h"

OECController::OECController() {

}

bool OECController::initialize() {

    std::cout << "sizeof(Event)"
              << sizeof(Event) << std::endl;
    return true;
}

const uint32_t* OECController::execute(const uint32_t* buffer) {



    return 0;
}

bool OECController::finalize() {
    return true;
}
