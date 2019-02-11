#!/bin/sh

echo `ls -l` > origine.txt
echo `./21sh`
echo `ls -l` > new.txt
echo `exit 42`
echo $?
echo `diff origine new`
