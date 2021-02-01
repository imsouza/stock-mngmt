#!/bin/bash
sleep 1.5
printf "\033c"
count=0
total=8
start=`date +%s`

while [ $count -lt $total ]; do
  sleep 0.5 # this is work
  cur=`date +%s`
  count=$(( $count + 1 ))
  pd=$(( $count * 73 / $total ))
  runtime=$(( $cur-$start ))
  estremain=$(( ($runtime * $total / $count)-$runtime ))
  printf "\r%d.%d%% Initializing in ($count of $total) - est %d:%0.2d remaining\e[K" \
  $(( $count*100/$total )) $(( ($count*1000/$total)%10)) \
  $(( $estremain/60 )) $(( $estremain%60 ))
done
printf "\nDone!\n"
sleep 0.8

if [ -e obj/main.o ] ; then
  cd obj && ./main.o
else
  make
fi