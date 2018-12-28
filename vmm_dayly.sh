#!/bin/bash

DATE=`date +%d%m%y`

cd /data/software/baranov/soft

if [[ -d /rawdata/$DATE ]];
then
  time ./vmm_root_compile.sh VMM.cxx $DATE > out/dayly.$DATE.log 2>&1 &
fi





