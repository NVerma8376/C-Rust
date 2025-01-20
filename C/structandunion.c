#include <stdio.h>
#include <string.h>

// Student structure
struct Student {
    char name[50];
    int rollNo;
    float marks;
};

// Point and Rectangle structures
struct Point {
    int x;
    int y;
};

struct Rectangle {
    struct Point topLeft;
    struct Point bottomRight;
};

// Employee structure
struct Employee {
    char name[50];
    int id;
};

// Node structure for linked list
struct Node {
    int data;
    struct Node* next;
};

// Union examples
union Data {
    int i;
    float f;
    char str[20];
};

union NumberConverter {
    int integer;
    float decimal;
};

// Variant structure with union
struct Variant {
    enum Type { INT, FLOAT, STRING } type;
    union Value {
        int i;
        float f;
        char* s;
    } value;
};

// Flags structure with bit fields
struct Flags {
    union {
        struct {
            unsigned int flag1 : 1;
            unsigned int flag2 : 1;
        } bits;
        unsigned int allFlags;
    };
};

// Hardware interface union
union PortRegister {
    struct {
        unsigned char bit0 : 1;
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
    } bits;
    unsigned char byte;
};

int main() {
    // Student example
    struct Student s1;
    strcpy(s1.name, "John");
    s1.rollNo = 1;
    s1.marks = 85.5;
    printf("\nStudent Details:\n");
    printf("Name: %s\nRoll No: %d\nMarks: %.2f\n", s1.name, s1.rollNo, s1.marks);

    // Rectangle example
    struct Rectangle rect;
    rect.topLeft.x = 0;
    rect.topLeft.y = 0;
    rect.bottomRight.x = 10;
    rect.bottomRight.y = 10;
    printf("\nRectangle Coordinates:\n");
    printf("Top Left: (%d,%d)\nBottom Right: (%d,%d)\n",
           rect.topLeft.x, rect.topLeft.y,
           rect.bottomRight.x, rect.bottomRight.y);

    // Employee array example
    struct Employee company[2];
    strcpy(company[0].name, "Alice");
    company[0].id = 101;
    strcpy(company[1].name, "Bob");
    company[1].id = 102;
    printf("\nEmployee Details:\n");
    for(int i = 0; i < 2; i++) {
        printf("Employee %d: %s (ID: %d)\n", i+1, company[i].name, company[i].id);
    }

    // Union Data example
    union Data data;
    data.i = 42;
    printf("\nUnion Data:\n");
    printf("Integer: %d\n", data.i);
    data.f = 3.14;
    printf("Float: %.2f\n", data.f);
    strcpy(data.str, "Hello");
    printf("String: %s\n", data.str);

    // NumberConverter example
    union NumberConverter conv;
    conv.integer = 123456;
    printf("\nNumber Converter:\n");
    printf("As integer: %d\n", conv.integer);
    printf("As float: %f\n", conv.decimal);

    // Variant example
    struct Variant var;
    var.type = INT;
    var.value.i = 42;
    printf("\nVariant Example:\n");
    printf("Integer value: %d\n", var.value.i);

    // Flags example
    struct Flags flags;
    flags.bits.flag1 = 1;
    flags.bits.flag2 = 0;
    printf("\nFlags:\n");
    printf("Flag1: %d, Flag2: %d\n", flags.bits.flag1, flags.bits.flag2);

    // PortRegister example
    union PortRegister port;
    port.byte = 0xFF;
    printf("\nPort Register:\n");
    printf("Bit 0: %d\n", port.bits.bit0);
    printf("Bit 7: %d\n", port.bits.bit7);

    return 0;
}
