#!/bin/bash

unset DATE
DATE=`date +%d%m%y`

unset EXEC
MYCXX=VMM_MainConvertor.cxx
EXEC=$(echo $MYCXX | cut -d "." -f1)
    
/bin/rm -rf out.$DATE.log
if [ -r $EXEC ]; then
   /bin/rm -rf $EXEC
fi
    
if [ -r $MYCXX ]; then
   echo $MYCXX "will compile soon"
   g++ $MYCXX -O2 `root-config --cflags` `root-config --libs --glibs` -o $EXEC
   ls -lartF ./$EXEC
else
   echo "any file for compilation is missing"
fi
    
if [ -r $EXEC ]; then
   ./$EXEC $@ > out.$DATE.log 2>&1 &
   wait
   /bin/rm -rf ./$EXEC
else
   echo "executable is missing"
fi

ls -lartFh /output/localDB




