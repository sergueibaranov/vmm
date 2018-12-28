#!/bin/bash

unset DATE
DATE=`date +%d%m%y`

unset EXEC
EXEC=$(echo $1 | cut -d "." -f1)

echo $EXEC

[ $# -lt 1 ] && { echo Usage: $0 filename is missing; exit 2 ;}
[ $# -lt 2 ] && { echo Usage: $0 datecode is missing; exit 3 ;}

if [ -r $EXEC ]; then
  /bin/rm -rf $EXEC
fi

if [ -r $1 ]; then
  echo $1 "will compile soon"
  g++ $1 -O2 `root-config --cflags` `root-config --libs --glibs` -o $EXEC
  ls -lartF ./$EXEC
else
  echo "any file for compilation is missing"
fi

sleep 1

echo " all parameters: " $@

/bin/rm -rf out/vmm.$DATE.log
if [ -r $EXEC ]; then
  ./$EXEC $@ > out/vmm.$DATE.log 2>&1 &
  wait
  /bin/rm -rf ./$EXEC
else 
  echo "executable is missing"
fi

# Converter for all
cd convertor

    unset EXEC
    MYCXX=VMM_MainConvertor.cxx
    EXEC=$(echo $MYCXX | cut -d "." -f1)
    
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
    
    /bin/rm -rf ../out/conv.$DATE.log
    if [ -r $EXEC ]; then
      ./$EXEC $@ > ../out/conv.$DATE.log 2>&1 &
      wait
      /bin/rm -rf ./$EXEC
    else
      echo "executable is missing"
    fi

ls -lartFh /output/localDB
cd ..

# Summary
cd mdidenko

    unset EXEC
    MYCXX=VMM_mainForComp.cxx
    EXEC=$(echo $MYCXX | cut -d "." -f1)

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

    /bin/rm -rf ../out/summary.$DATE.log
    if [ -r $EXEC ]; then
      ./$EXEC $@ > ../out/summary.$DATE.log 2>&1 &
      wait
      /bin/rm -rf ./$EXEC
    else
      echo "executable is missing"
    fi

ls -lartFh /var/www/html/www/summary/histogram/HIST_*.pdf
ls -lartFh /var/www/html/www/summary/best_test/Database.txt
cd ..

