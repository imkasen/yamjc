#!/usr/bin/env bash

set -Eeuo pipefail

if [[ -d benchmark/ ]]; then
    rm -rf benchmark/
fi

if [[ ! -d build/ ]]; then
    mkdir build && cd build
    cmake .. && make
fi

if [[ -e build/compiler && -e resource/tests/SumIf.java ]]; then
    mkdir benchmark/ && cd benchmark/
    cp ../build/compiler .
    cp ../resource/tests/SumIf.java .

    # Compiler

    START=$(date +%s%N)
    for ((i=1;i<10;++i))
    do
        # modify nums in 'SumIf.java'
        # e.g.  System.out.println(new Test().Sum(10k/100k/...));
        javac SumIf.java
        rm ./*.class
    done
    END=$(date +%s%N)
    TOTAL1=$(("$END" - "$START"))
    echo "OpenJDK compiler   total elapsed time: ${TOTAL1} ns"

    START=$(date +%s%N)
    for ((i=1;i<10;++i))
    do
        ./compiler SumIf.java
        rm ./*.dot ./*.class
    done
    END=$(date +%s%N)
    TOTAL2=$(("$END" - "$START"))
    echo "Mini java compiler total elapsed time: $TOTAL2 ns"

    awk "BEGIN {print $TOTAL2/$TOTAL1}"

    # Compiler and Interpreter

    START=$(date +%s%N)
    for ((i=1;i<10;++i))
    do
        javac SumIf.java
        java SumIf > /dev/null
        # java -Xss256m SumIf > /dev/null
        rm ./*.class
    done
    END=$(date +%s%N)
    TOTAL1=$(("$END" - "$START"))
    echo "OpenJDK                            total elapsed time: ${TOTAL1} ns"

    START=$(date +%s%N)
    for ((i=1;i<10;++i))
    do
        ./compiler -i SumIf.java > /dev/null
        rm ./*.dot ./*.class
    done
    END=$(date +%s%N)
    TOTAL2=$(("$END" - "$START"))
    echo "Mini java compiler and interpteter total elapsed time: $TOTAL2 ns"

    awk "BEGIN {print $TOTAL2/$TOTAL1}"

    cd .. && rm -rf benchmark/
fi
