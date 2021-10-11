#!/usr/bin/env bash

set -e
set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

print_header "RUN cppcheck"
if [ "${1}" == "--local" ]; then
  CPPCHECK="cppcheck"
else
  CPPCHECK="./linters/cppcheck/cppcheck"
fi
${CPPCHECK} project tests --enable=all --error-exitcode=1 -I project/ --suppress=missingIncludeSystem # --check-config

print_header "RUN cpplint.py"
python2.7 ./linters/cpplint/cpplint.py --extensions=c project/*
python2.7 ./linters/cpplint/cpplint.py --extensions=cpp --filter=-runtime/references,-legal/copyright,-build/include_subdir,-whitespace/line_length tests/*

print_header "SUCCESS"
