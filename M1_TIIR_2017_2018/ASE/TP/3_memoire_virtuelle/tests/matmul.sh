#!/usr/bin/env bash

echo "=== MATMUL ==="
../build/bin/mmu_manager > matmul.out

echo "=== ORACLE ==="
../build/bin/oracle < matmul.out
echo ""