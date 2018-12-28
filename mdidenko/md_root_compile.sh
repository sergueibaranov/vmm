#!/bin/bash

unset DATE
DATE=`date +%d%m%y`

# Converter for all                                                                                                                                                                                  

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
      ./$EXEC $@ > ../out/summary.$DATE.log &
      wait
      /bin/rm -rf ./$EXEC
    else
      echo "executable is missing"
    fi

ls -lartFh /var/www/html/www/summary/best_test/Database.txt
ls -lartFh /var/www/html/www/summary/histogram/HIST*.pdf
