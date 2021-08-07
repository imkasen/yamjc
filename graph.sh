#!/usr/bin/env bash

set -Eeuo pipefail

if [[ $# -eq 0 ]]; then
  dot -T svg ast.dot -o ast.svg
  dot -T svg st.dot -o st.svg
elif [[ $# -eq 1 && $1 == "ast" ]]; then
  dot -T svg ast.dot -o ast.svg
elif [[ $# -eq 1 && $1 == "st" ]]; then
  dot -T svg st.dot -o st.svg
fi
