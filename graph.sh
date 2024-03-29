#!/usr/bin/env bash

set -Eeuo pipefail

if [[ -e ast.dot ]]; then
  dot -T svg ast.dot -o ast.svg
fi

if [[ -e st.dot ]]; then
  dot -T svg st.dot -o st.svg
fi

if [[ -e cfg.dot ]];then
  dot -T svg cfg.dot -o cfg.svg
fi
