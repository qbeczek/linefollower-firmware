cmake_minimum_required(VERSION 3.22)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})


project(DTS)
target_sources(app PRIVATE src/main.c)
