#!/usr/bin/env bash
set -e

echo "=== Installing Conan dependencies for Linux ==="

rm -f CMakeUserPresets.json CMakePresets.json

# Linux 64-Bit
echo "--> Linux x64 (Debug & Release)..."
conan install . -pr:h=./conan/profiles/linux-x64 -s build_type=Debug -b=missing
conan install . -pr:h=./conan/profiles/linux-x64 -s build_type=Release -b=missing

# Linux 32-Bit | uncomment for 32-bit builds
#echo "--> Linux x86 (Debug & Release)..."
#conan install . -pr:h=./conan/profiles/linux-x86 -s build_type=Debug -b=missing
#conan install . -pr:h=./conan/profiles/linux-x86 -s build_type=Release -b=missing

echo "=== Done! You can now use your IDE or 'cmake --preset <preset>' ==="