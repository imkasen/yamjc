#!/usr/bin/env bash

set -Eeuo pipefail

ast() {
  dot -T svg ast.dot -o ast.svg
}

st() {
  dot -T svg st.dot -o st.svg
}

if [[ $# -eq 0 ]]; then
  ast
  st
elif [[ $# -eq 1 && $1 == "ast" ]]; then
  ast
elif [[ $# -eq 1 && $1 == "st" ]]; then
  st
fi
