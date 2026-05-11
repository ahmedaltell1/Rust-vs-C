cmake_minimum_required(VERSION 3.27)
project(hash_digest_verif C)

set(CMAKE_C_STANDARD 99)

add_executable(hash_digest_verif main.c
        aes128.c
        aes.c)
