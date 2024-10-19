#!/bin/bash

find . -name '*.cpp' -o -name '*.h' | xargs clang-format -i
pre-commit run --all-files
