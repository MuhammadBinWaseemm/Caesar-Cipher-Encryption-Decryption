# Caesar-Cipher-Encryption-Decryption
This repository contains a C++ implementation of the Caesar Cipher, a classical substitution cipher technique. Developed as part of the CY-211 (Information Security) course at GIKI, this assignment demonstrates how to perform simple encryption and decryption using a fixed shift.

### Features:

- **Encryption**: Implemented in `Encryption.cpp`. Takes input from the user and outputs the encrypted text based on a shift key.
- **Decryption**: Implemented in `Decryption.cpp`. Uses statistical frequency analysis and brute force to determine the best possible decrypted result.

## Files

### `Encryption.cpp`
- Asks user for input text (alphabetic only).
- Asks for a numeric key.
- Shifts each letter by the key modulo 26.
- Outputs the encrypted ciphertext.

### `Decryption.cpp`
- Accepts the encrypted text.
- Calculates multiple decryption guesses based on:
  - Brute-force key shifting (0 to 25).
  - Fixed English letter frequency matching.
- Prompts the user to select the best result or request more guesses.


