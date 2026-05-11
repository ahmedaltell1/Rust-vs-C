# Rust vs C Security and Performance Research

## Overview

This project was developed as part of a memory safety and systems programming research internship focused on comparing the security, reliability, and performance characteristics of the C and Rust programming languages.

The research explored how both languages handle low-level systems programming tasks such as hashing, cryptographic file verification, encryption/decryption workflows, and source-code translation concepts.

The project consists of equivalent implementations written in both C and Rust to evaluate differences in:
- Memory safety
- Performance
- Developer tooling
- Security guarantees
- Reliability in systems-level applications

---

## Research Objectives

The primary goals of this research were:

- Compare memory-safe and memory-unsafe programming paradigms
- Analyze practical differences between Rust and C in systems programming
- Implement equivalent cryptographic workflows in both languages
- Evaluate performance and security tradeoffs
- Explore automated translation concepts from C to Rust

---

## Implemented Projects

### 1. SHA-256 File Verification

Developed two equivalent programs:
- One written in C
- One written in Rust

Each program:
- Reads a target file
- Computes its SHA-256 hash digest
- Compares the generated digest with a known expected digest
- Verifies file authenticity and integrity

---

### 2. AES-128 File Decryption and Authentication

Developed two equivalent AES-128 ECB decryption programs:
- One in C
- One in Rust

Each implementation:
- Reads an encrypted file
- Decrypts the file using a predefined AES-128 key
- Verifies file authenticity using SHA-256 hashing

---

## Key Research Areas

- Memory safety
- Cryptographic verification
- Systems programming
- File integrity validation
- AES encryption/decryption
- SHA-256 hashing
- Safe vs unsafe programming
- Performance benchmarking
- Low-level software security

---

## Technologies Used

### Languages
- C
- Rust

### Cryptography
- SHA-256
- AES-128 ECB

### Tools
- GCC
- Cargo
- Linux command-line tools

---

## External Libraries and Credits

Some cryptographic functionality used in the C implementations relies on external open-source libraries that were not developed by me.

The SHA-256 implementation used in the C portion of this project was adapted from publicly available open-source repositories for educational and research purposes.

Proper credit belongs to the original library authors and maintainers.

Example library referenced:
- SHA-2 Library: https://github.com/amosnier/sha-2

Rust implementations primarily utilized existing Rust cryptographic crates available through Cargo.
