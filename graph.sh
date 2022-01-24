#!/usr/bin/env bash

set -Eeuo pipefail

ast() {
  dot -T svg ast.dot -o ast.svg
}

st() {
  dot -T svg st.dot -o st.svg
}

if [[ -e ast.dot ]]; then
  ast
fi

if [[ -e st.dot ]]; then
  st
fi
