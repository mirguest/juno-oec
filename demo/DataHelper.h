#ifndef DataHelper_h
#define DataHelper_h

/*
 * Overivew
 *
 * The classes and functions defined in this header file are used to represent data model in memory.
 *
 */

/*
 * An event data model including
 * * event timestamp (4+4 bytes)
 * * reconstructed vertex (3*4 bytes), time, energy (4 bytes)
 * * flag0, flag1 (4+4 bytes)
 * * etc.
 */
struct Event {
    int evt_time_second; // second part
    int evt_time_nanosec; // nanosec part

    float x;  // vertex
    float y;
    float z;

    float energy; // energy

    uint32_t flag0; // set from rec alg

    uint32_t flag1; // classification
};


/*
 * Data Decoding is a helper class to decode the input data.
 */

#endif
