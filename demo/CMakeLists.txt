
add_library(oec-demo SHARED
    OECController.cpp
    OECConfigMgr.cpp
    OECProcessor.cpp
    OECClassifier.cpp

    DataHelper.cpp
)

add_executable(oec-daq
    DAQEmulator.cpp
    demo.cpp
)

target_link_libraries(oec-daq
    oec-demo
)