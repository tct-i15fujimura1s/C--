#!/bin/sh

INCDIR=/usr/local/cmmInclude
LIBDIR=/usr/local/cmmLib

for i in $*; do
    j=`basename ${i}`
    n=`expr ${j} : '\([^\.]*\)'`
    echo '[!!!' "${n}.cmm => ${n}.s" '!!!]'
   cc -E -std=c99 -nostdinc -I${INCDIR} -I${LIBDIR} - < ${i} |
    ../../../src/vm-c-- -O > ${n}.s
done
