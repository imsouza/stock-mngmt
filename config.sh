#!/bin/bash

if [ -e obj/main.o ] ; then
  cd obj && ./main.o
else
  make && cd obj && ./main.o
fi