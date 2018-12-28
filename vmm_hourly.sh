#!/bin/bash

DATE=`date +%d%m%Y`

cd /data/software/baranov/soft

if [[ -d /rawdata/$DATE ]];
then
  time ./vmm_root_get_rawdata.sh VMM.cxx $DATE > out/hourly.$DATE.log 2>&1 &
fi





