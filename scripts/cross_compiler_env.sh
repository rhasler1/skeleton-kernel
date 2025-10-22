#!/usr/bin/env bash
# cross-compiler environment setup for AArch64 (Raspberry Pi 5)

export PREFIX="$HOME/opt/cross"
export TARGET="aarch64-elf"
export PATH="$PREFIX/bin:$PATH"

echo "---Set the following environment variables for this session---"
echo "PREFIX=   $PREFIX"
echo "TARGET=   $TARGET"
echo "PATH=     $PATH"
echo ""

CC="$TARGET-gcc"
echo "---Searching for cross compiler---"
if ! command -v "$CC" &>/dev/null; then
    echo "Compiler not found: $CC"
else
    echo "Compiler found: $CC"
fi
echo ""
