#!/bin/sh
output=$(./test_uqGslMatrixConstructorFatal 2>&1)
ret=$?
if [ $ret != 0 ]
then
  exit 0
fi

if [ $ret == 0 ]
then
  exit 1
fi
