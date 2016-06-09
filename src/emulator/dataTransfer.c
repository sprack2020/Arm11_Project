#include "dataTransfer.h"

// prototypes
static uint32_t calculateOffset(uint32_t offsetBits, bool isImmediateOffset);
static void load(uint32_t toLoadAddr, uint32_t Rd);
static void store(uint32_t RnVal, uint32_t Rd);
static bool checkValidAddress(uint32_t address);
static int retrievePinIndexes(uint32_t pinsToSet, int *setPins);
static bool isOutput(int pin);
static bool isCleared(int pin);
static void turnOn(int pin);
static uint32_t getGPIOAddrType(uint32_t addr);
static void setClear(int pin);
static void handleControlPortSDT(bool isLoad, uint32_t Rd, uint32_t address,
                          uint32_t addrType);
static void writeToControlPort(uint32_t addrType, uint32_t Rd);
static void writeToDataPort(uint32_t Rd, uint32_t addrType);
static int getIndexLower(uint32_t addrType);
bool isDataPort(uint32_t bigEndianAddr);

// PRE: instr is a data transfer instruction
// behavior: Loads/stores access of memory as described in spec
void dataTransfer(uint32_t instr) {
    // get I, L, U, Rn, Rd, P, offset
    bool isImmediateOffset = extractBit(instr, IMM_BIT);
    bool isPreIndex = extractBit(instr, PREPOST_BIT);
    bool isUp = extractBit(instr, UP_BIT);
    bool isLoad = extractBit(instr, LOAD_BIT);
    uint32_t Rn = extractBits(instr, Rn_UPPER, Rn_LOWER);
    uint32_t Rd = extractBits(instr, Rd_UPPER, Rd_LOWER);
    uint32_t offset = calculateOffset(instr, isImmediateOffset);

    // check valid registers used
    if (Rd == PC_INDEX) {
        fprintf(stderr, "Error in dataTransfer: Attempting to use PC as source"
            " / destination register\n");
        exit(2);
    }

    // apply offset to base register
    uint32_t adjustedRnVal = isUp ? REGFILE[Rn] + offset : REGFILE[Rn] - offset;

    // choose correct base register
    uint32_t address = isPreIndex ? adjustedRnVal : REGFILE[Rn];

    uint32_t addrType = getGPIOAddrType(address);
    switch (addrType) {
        case CONTROL0_9:
        case CONTROL10_19:
        case CONTROL20_29:
            handleControlPortSDT(isLoad, Rd, address, addrType);
            break;

        case CLEAR_PORTS:
        case ON_PORTS:
            if (isLoad) {
                REGFILE[Rd] = address;
            } else {
                writeToDataPort(Rd, addrType);
            }
            break;

        case NOTGPIO:
            if (isLoad) {
                load(address, Rd);
            } else {
                store(address, REGFILE[Rd]);
            }
            break;

        default:
            printf("Error: Out of bounds memory access at address 0x%08x\n",
                   address);
    }

    // if post index, now adjust the base register
    if (!isPreIndex) {
        REGFILE[Rn] = adjustedRnVal;
    }
}

// attempts to write Rd to the clear / write port, depending on the addrType
static void writeToDataPort(uint32_t Rd, uint32_t addrType) {
    // fill pinsToSet with the correct pins and get the number pins to set
    int pinsToSet[MAX_PIN];
    int numPinsToSet = retrievePinIndexes(REGFILE[Rd], pinsToSet);
    int pin;

    for (int i = 0; i < numPinsToSet; i++) {
        pin = pinsToSet[i];
        assert(pin >= 0 && pin <= MAX_PIN);

        if (addrType == ON_PORTS) {
            // set pin's ON bit and prints that it is on
            turnOn(pin);
        } else if (addrType == CLEAR_PORTS) {
            // sets pin's OFF bit and prints that it is off
            setClear(pin);
        } else {
            // something went wrong, address is not GPIO. Note addrType
            // should be the address here
            fprintf(stderr, "Error in SDT: writeToDataPort: address (Big "
                    "Endian) %u is not a data port\n", addrType);
            exit(EXIT_FAILURE);
        }
    }
}

// handles the case where we are performing an SDT on the control ports
static void handleControlPortSDT(bool isLoad, uint32_t Rd, uint32_t address,
        uint32_t addrType) {
    if (isLoad) {
        // load address into Rd and print pin accessed
        REGFILE[Rd] = address;

        // print that GPIO has been accessed
        int indexLower = getIndexLower(addrType);
        printf("%s%i%s%i%s\n", "One GPIO pin from ", indexLower, " to ",
               indexLower + CONTROL_PORT_WIDTH - 1, " has been accessed");

    // is a store instruction
    } else {
        writeToControlPort(addrType, Rd);
    }
}

static int getIndexLower(uint32_t addrType) {
    int lowerIdx;

    switch (addrType) {
        case CONTROL0_9:
            lowerIdx = 0;
            break;

        case CONTROL10_19:
            lowerIdx = 10;
            break;

        case CONTROL20_29:
            lowerIdx = 20;
            break;

        default:
            assert(false);
    }

    return lowerIdx;
}

// writes Rd to the control port selected by addrType
static void writeToControlPort(uint32_t addrType, uint32_t Rd) {
    int indexLower = getIndexLower(addrType);
     printf("%s%i%s%i%s\n", "One GPIO pin from ", indexLower, " to ",
            indexLower + CONTROL_PORT_WIDTH - 1, " has been accessed");

    // write to control port
    switch (addrType) {
        case CONTROL0_9:
            state.controlBitsGPIO0To9 = REGFILE[Rd];
            break;

        case CONTROL10_19:
            state.controlBitsGPIO10To19 = REGFILE[Rd];
            break;

        case CONTROL20_29:
            state.controlBitsGPIO20To29 = REGFILE[Rd];
            break;

        default:
            assert(false);
    }
}

// calculates and returns the offset to add to the base register
static uint32_t calculateOffset(uint32_t instr, bool isImmediateOffset) {
    // handling offset bits is equivalent to getting second operand in
    // data process, but with the immediate offset flag negated
    return getOperand2(instr, !isImmediateOffset).result;
}

// Loads the data from MEM[Rn] into Rd
static void load(uint32_t toLoadAddr, uint32_t Rd) {
    assert(checkValidAddress(toLoadAddr));

    read32Bits(&REGFILE[Rd], &MEM[toLoadAddr]);
    swapEndianness(&REGFILE[Rd]);
}

// stores the data from Rn into memory starting at address Rd
static void store(uint32_t RnVal, uint32_t toStore) {
    assert(checkValidAddress(RnVal));

    const int n = REG_LENGTH / MEM_LENGTH;

    for (int i = n - 1; i >= 0; i--) {
        MEM[RnVal + i] = extractBits(toStore, (i + 1) * MEM_LENGTH - 1,
                i * MEM_LENGTH);
    }
}

static bool checkValidAddress(uint32_t address) {
    return (address + (REG_LENGTH / MEM_LENGTH) - 1 <= MEM_SIZE);
}

// Gets the indexes of the set bits in pinsToSet, putting them into setPins,
// and returns the number of pins to set
static int retrievePinIndexes(uint32_t pinsToSet, int *setPins) {
    int numPins = 0;

    for (int i = 0; i <= MAX_PIN; i++) {
        if (extractBit(pinsToSet, i)) {
            setPins[numPins] = i;
            numPins++;
        }
    }

    return numPins;
}

// is the pin's control bit set
static bool isOutput(int pin) {
    uint32_t pinControlIndex = (uint32_t) (pin % 10) * 3;
    switch (pin / CONTROL_PORT_WIDTH) {
        case 0:
            return extractBit(pinControlIndex, state.controlBitsGPIO0To9);
        case 1:
            return extractBit(pinControlIndex, state.controlBitsGPIO10To19);
        case 2:
            return extractBit(pinControlIndex, state.controlBitsGPIO20To29);
        default:
            fprintf(stderr, "invalid pin in isOutput: %i", pin);
            exit(EXIT_FAILURE);
    }
}

// is the pin's clear bit set
static bool isCleared(int pin) {
    return extractBit(pin, state.clearPins);
}

// set a certain pin's write bti
static void turnOn(int pin) {
    assert(isOutput(pin) && isCleared(pin));

    state.onPins = updateBit(state.onPins, pin, 1);
    puts("PIN ON");
}

// gets what kind of GPIO address addr is i.e. what control port / data port
static uint32_t getGPIOAddrType(uint32_t addr) {
    uint32_t bigEndianAddr = addr;
    swapEndianness(&bigEndianAddr);

    if (isDataPort(bigEndianAddr)) {
        return bigEndianAddr;
    } else if (addr <= MEM_SIZE) {
        return NOTGPIO;
    } else {
        return addr;
    }
}

bool isDataPort(uint32_t bigEndianAddr) {
    return bigEndianAddr == CONTROL0_9 || bigEndianAddr == CONTROL20_29 ||
            bigEndianAddr == CONTROL10_19;
}

// sets the pin's clear bit
static void setClear(int pin) {
    updateBit(state.clearPins, pin, 1);
    puts("PIN OFF");
}
