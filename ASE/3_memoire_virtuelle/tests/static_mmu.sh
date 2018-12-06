#!/usr/bin/env bash

echo "=== test_mmu ==="
../build/bin/basic_mmu
echo ""

echo "=== static_mmu ==="
../build/bin/static_mmu
echo ""