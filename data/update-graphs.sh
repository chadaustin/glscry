#!/bin/sh
for a in *.data.sh; do
  echo $a && sh $a
done
