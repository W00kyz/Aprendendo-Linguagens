#include <iostream>
#include <string>

using namespace std;

int main() {

    // Conversões

    bool b = 42; // Verdadeiro, falso somente quando for igual a 0.
    int i = b; // i = 1.
    i = 3.14; // i = 3
    double pi = i; // pi = 3.0
    unsigned char c = -1; // c = 255 (range 0-255)
    signed char c2 = 256; // undefined max 255 (range -256<->255)

    // Literals
    pi = 3.14159E0;
    int decimal = 20;
    decimal = 024; // 20 em octal
    decimal = 0x14; // 20 em hexadecimal
    char a = 'a'; // char
    string ab = u8"\u0444"; // utf-8 string
    wchar_t d = L'a'; // wide character (não imprime o caractere em si, apenas o código)
    return 0;
}