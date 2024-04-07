#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define ROTORS_COUNTS 5
#define NUMBER_OF_RINGS 5
#define ESC 27
#define ALPHABET_LENGTH 26

struct PlugBoardConnection {
    char from;
    char to;
} plugBoardConnections[13];

char alphabet[ALPHABET_LENGTH] = {
        'a',
        'b',
        'c',
        'd',
        'e',
        'f',
        'g',
        'h',
        'i',
        'j',
        'k',
        'l',
        'm',
        'n',
        'o',
        'p',
        'q',
        'r',
        's',
        't',
        'u',
        'v',
        'w',
        'x',
        'y',
        'z'
};

char map[ROTORS_COUNTS][ALPHABET_LENGTH][2] = {
        {
                {'a', 'e'},
                {'b', 'k'},
                {'c', 'w'},
                {'d', 'f'},
                {'e', 'l'},
                {'f', 'g'},
                {'g', 'd'},
                {'h', 'q'},
                {'i', 'v'},
                {'j', 'z'},
                {'k', 'n'},
                {'l', 't'},
                {'m', 'o'},
                {'n', 'w'},
                {'o', 'y'},
                {'p', 'h'},
                {'q', 'x'},
                {'r', 'u'},
                {'s', 's'},
                {'t', 'p'},
                {'u', 'a'},
                {'v', 'i'},
                {'w', 'b'},
                {'x', 'r'},
                {'y', 'c'},
                {'z', 'y'}
        },
        {
                {'a', 'a'},
                {'b', 'j'},
                {'c', 'd'},
                {'d', 'k'},
                {'e', 's'},
                {'f', 'i'},
                {'g', 'r'},
                {'h', 'u'},
                {'i', 'x'},
                {'j', 'b'},
                {'k', 'l'},
                {'l', 'h'},
                {'m', 'w'},
                {'n', 't'},
                {'o', 'm'},
                {'p', 'c'},
                {'q', 'q'},
                {'r', 'g'},
                {'s', 'z'},
                {'t', 'n'},
                {'u', 'p'},
                {'v', 'y'},
                {'w', 'f'},
                {'x', 'v'},
                {'y', 'o'},
                {'z', 'e'}
        },
        {
                {'a', 'b'},
                {'b', 'd'},
                {'c', 'f'},
                {'d', 'h'},
                {'e', 'j'},
                {'f', 'l'},
                {'g', 'c'},
                {'h', 'p'},
                {'i', 'r'},
                {'j', 't'},
                {'k', 'x'},
                {'l', 'v'},
                {'m', 'z'},
                {'n', 'n'},
                {'o', 'y'},
                {'p', 'e'},
                {'q', 'i'},
                {'r', 'w'},
                {'s', 'g'},
                {'t', 'a'},
                {'u', 'k'},
                {'v', 'm'},
                {'w', 'u'},
                {'x', 's'},
                {'y', 'q'},
                {'z', 'o'}
        },
        {
                {'a', 'e'},
                {'b', 's'},
                {'c', 'o'},
                {'d', 'v'},
                {'e', 'p'},
                {'f', 'z'},
                {'g', 'j'},
                {'h', 'a'},
                {'i', 'y'},
                {'j', 'q'},
                {'k', 'u'},
                {'l', 'i'},
                {'m', 'r'},
                {'n', 'h'},
                {'o', 'x'},
                {'p', 'l'},
                {'q', 'n'},
                {'r', 'f'},
                {'s', 't'},
                {'t', 'g'},
                {'u', 'k'},
                {'v', 'd'},
                {'w', 'c'},
                {'x', 'm'},
                {'y', 'w'},
                {'z', 'b'}
        },
        {
                {'a', 'v'},
                {'b', 'z'},
                {'c', 'b'},
                {'d', 'r'},
                {'e', 'g'},
                {'f', 'i'},
                {'g', 't'},
                {'h', 'y'},
                {'i', 'u'},
                {'j', 'p'},
                {'k', 's'},
                {'l', 'd'},
                {'m', 'n'},
                {'n', 'h'},
                {'o', 'l'},
                {'p', 'x'},
                {'q', 'a'},
                {'r', 'w'},
                {'s', 'm'},
                {'t', 'j'},
                {'u', 'q'},
                {'v', 'o'},
                {'w', 'f'},
                {'x', 'e'},
                {'y', 'c'},
                {'z', 'k'}
        }
};

char reflectorMap[ALPHABET_LENGTH][2] = {
        {'a', 'y'},
        {'b', 'r'},
        {'c', 'u'},
        {'d', 'h'},
        {'e', 'q'},
        {'f', 's'},
        {'g', 'l'},
        {'h', 'd'},
        {'i', 'p'},
        {'j', 'x'},
        {'k', 'n'},
        {'l', 'g'},
        {'m', 'o'},
        {'n', 'k'},
        {'o', 'm'},
        {'p', 'i'},
        {'q', 'e'},
        {'r', 'b'},
        {'s', 'f'},
        {'t', 'z'},
        {'u', 'c'},
        {'v', 'w'},
        {'w', 'v'},
        {'x', 'j'},
        {'y', 'a'},
        {'z', 't'}
};

int rotorSettings[ROTORS_COUNTS] = {
        4,
        5,
        2,
        1,
        1,
};


struct Rotor {
    int id;
    int rings;
    char map[ALPHABET_LENGTH][2];
} rotors[ROTORS_COUNTS], reflector;


/**
 * Get mapped index for alphabet
 * @param rotor
 * @param value
 * @return
 */
int getRotorMapAlphabet(struct Rotor *rotor, char value) {
    for (int index = 0; index < ALPHABET_LENGTH; index++) {
        if (rotor->map[index][0] == value) {
            return index;
        }
    }
    return -1;
}

/**
 * Get mapped index wiring
 * @param rotor
 * @param value
 * @return
 */
int getRotorMapWiring(struct Rotor *rotor, int value) {
    for (int index = 0; index < ALPHABET_LENGTH; index++) {
        if (rotor->map[index][1] == value) {
            return index;
        }
    }
    return -1;
}

int getAlphabetCharIndex(char entry) {
    for (int index = 0; index < ALPHABET_LENGTH; index++) {
        if (alphabet[index] == entry) {
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
    for (int index = 0; index < ROTORS_COUNTS; index++) {
        struct Rotor *curr = &rotors[index];

        curr->id = index;
        curr->rings = rotorSettings[index];

        // Assign map to each rotor's map
        for (int i = 0; i < ALPHABET_LENGTH; i++) {
            curr->map[i][0] = map[index][i][0];
            curr->map[i][1] = map[index][i][1];
        }
    }

    struct Rotor *reflectorPointer = &reflector;
    reflectorPointer->id = -1;
    reflectorPointer->rings = -1;
    for (int index = 0; index < ALPHABET_LENGTH; index++) {
        reflectorPointer->map[index][0] = reflectorMap[index][0];
        reflectorPointer->map[index][1] = reflectorMap[index][1];
    }
};

/**
 * Gets specific rotor
 * @param index index of rotor
 * @return Rotor
 */
struct Rotor *getRotorById(int index) {
    if (index >= ROTORS_COUNTS || index < 0) {
        fprintf(stderr, "Index is out of bound!");
        exit(EXIT_FAILURE);
    }
    return &rotors[index];
}

void shiftMap(struct Rotor *rotor) {
    char lastChar = rotor->map[ALPHABET_LENGTH - 1][0];

    char temp = rotor->map[0][0];
    for (int index = 0; index < ALPHABET_LENGTH - 1; index++) {
        char nextTemp = rotor->map[index + 1][0];
        rotor->map[index + 1][0] = temp;
        temp = nextTemp;
    }

    // Writes last character to the first one
    rotor->map[0][0] = lastChar;
}

/**
 * Changes router positions on input
 */
void inputHandler() {
    // Iterate over each router
    for (int index = 0; index < ROTORS_COUNTS - 1; index++) {
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
    int currentEntryIndex = getAlphabetCharIndex(entry);

    // First pass through
    for (int index = 0; index < ROTORS_COUNTS; index++) {
        struct Rotor *curr = getRotorById(index);
        char value = curr->map[currentEntryIndex][1];

        currentEntryIndex = getAlphabetCharIndex(value);
    }

    // Reflector logic
    struct Rotor *reflectorPointer = &reflector;
    char value = reflectorPointer->map[currentEntryIndex][1];

    for (int index = 0; index < ALPHABET_LENGTH; index++) {
        if (reflectorPointer->map[index][0] == value) {
            currentEntryIndex = index;
            break;
        }
    }

    // Back pass through
    for (int index = ROTORS_COUNTS - 1; index >= 0; index--) {
        struct Rotor *curr = getRotorById(index);
        char backPassValue = curr->map[currentEntryIndex][0];

        for(int backPassIndex = 0; backPassIndex < ALPHABET_LENGTH; backPassIndex++){
            if(curr->map[backPassIndex][1] == backPassValue){
                currentEntryIndex = backPassIndex;
                break;
            }
        }
    }


    // Check for plug board re-wiring, if found it sets entry char to mapped charreturn alphabet[currentEntryIndex];
}


int main() {
    // Variables
    bool runtime = true;

    // Setup
    setRotorsAndReflector();

    const bool FUNCTION_CODE = 1;

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
