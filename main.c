#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define ROUTERS_COUNTS 3
#define NUMBER_OF_RINGS 5
#define ESC 27
#define ALPHABET_LENGTH 26

struct PlugBoardConnection {
    char from;
    char to;
};

char map[ALPHABET_LENGTH][2] = {
        {'a', 'd'},
        {'b', 'b'},
        {'c', 'e'},
        {'d', 'f'},
        {'e', 'g'},
        {'f', 'h'},
        {'g', 'i'},
        {'h', 'j'},
        {'i', 'm'},
        {'j', 'n'},
        {'k', 'p'},
        {'l', 'o'},
        {'m', 'v'},
        {'n', 'w'},
        {'o', 'z'},
        {'p', 'y'},
        {'q', 'k'},
        {'r', 'a'},
        {'s', 'r'},
        {'t', 'l'},
        {'u', 's'},
        {'v', 'o'},
        {'w', 'u'},
        {'x', 't'},
        {'y', 'x'},
        {'z', 'q'}
};


struct Rotor {
    int id;
    int rings;
    char map[ALPHABET_LENGTH][2];
} rotors[ROUTERS_COUNTS], reflector;


/**
 * Get mapped index
 * @param rotor
 * @param value
 * @return
 */
int getRotorMap(struct Rotor *rotor, char value) {
    for (int index = 0; index < ALPHABET_LENGTH; index++) {
        if (rotor->map[index][0] == value) {
            return index;
        }
    }
    return -1;
}

/**
 * Sets routers array
 * @return void
 */
void setRotorsAndReflector() {
    for (int index = 0; index < ROUTERS_COUNTS; index++) {
        struct Rotor *curr = &rotors[index];

        curr->id = index;
        curr->rings = 1;

        // Assign map to each rotor's map
        for (int i = 0; i < ALPHABET_LENGTH; i++) {
            curr->map[i][0] = map[i][0];
            curr->map[i][1] = map[i][1];
        }
    }

    struct Rotor *reflectorPointer = &reflector;
    reflectorPointer->id = -1;
    reflectorPointer->rings = -1;
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        reflectorPointer->map[i][0] = map[i][0];
        reflectorPointer->map[i][1] = map[i][1];
    }
};

/**
 * Gets specific rotor
 * @param index index of rotor
 * @return Rotor
 */
struct Rotor *getRotorById(int index) {
    if (index >= ROUTERS_COUNTS || index < 0) {
        fprintf(stderr, "Index is out of bound!");
        exit(EXIT_FAILURE);
    }
    return &rotors[index];
}

void shiftMap(struct Rotor *rotor) {
    char lastChar = rotor->map[ALPHABET_LENGTH - 1][1];

    char temp = rotor->map[0][1];
    for (int index = 0; index < ALPHABET_LENGTH - 1; index++) {
        char nextTemp = rotor->map[index + 1][1];
        rotor->map[index + 1][1] = temp;
        temp = nextTemp;
    }

    // Writes last character to the first one
    rotor->map[0][1] = lastChar;
}

/**
 * Changes router positions on input
 */
void inputHandler() {
    // Iterate over each router
    for (int index = 0; index < ROUTERS_COUNTS - 1; index++) {
        struct Rotor *curr = getRotorById(index);
        struct Rotor *nextRotor = getRotorById(index + 1);

        // If its first ring always increment
        if (curr->id == 0) {
            curr->rings = curr->rings + 1;
            shiftMap(curr);
        }

        // Check if current router has reached the maximum value
        if (curr->rings == NUMBER_OF_RINGS - 1) {
            // Reset current router to 0
            curr->rings = 1;
            shiftMap(curr);

            // Increment next router if it exists
            if (nextRotor != NULL) {
                nextRotor->rings = (nextRotor->rings + 1) % NUMBER_OF_RINGS;
                shiftMap(nextRotor);
            }
        }
    }
}

/**
 * Encoding the character
 * @param entry
 * @return
 */
char encode(char entry) {
    char currentEntry = entry;

    // First pass through
    for (int index = 0; index < ROUTERS_COUNTS; index++) {
        struct Rotor *curr = getRotorById(index);
        currentEntry = curr->map[getRotorMap(curr, currentEntry)][1];
    }

    // Reflector
    struct Rotor *reflectorPointer = &reflector;
    currentEntry = reflectorPointer->map[getRotorMap(reflectorPointer, currentEntry)][1];

    // First pass through
    for (int index = ROUTERS_COUNTS - 1; index >= 0; index--) {
        struct Rotor *curr = getRotorById(index);
        currentEntry = curr->map[getRotorMap(curr, currentEntry)][1];
    }

    return currentEntry;
}

int main() {
    // Variables
    bool runtime = true;

    // Setup
    setRotorsAndReflector();

    // Main runtime
    while (runtime) {
        char key;
        scanf(" %c", &key);

        if (key == ESC) {
            printf("ESC key pressed. Exiting...\n");
            runtime = false;
            break;
        }

        printf("%c", encode(key));
        inputHandler();
    }
    return 0;
}
