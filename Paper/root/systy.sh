#!/bin/sh

for myf in WP95 WP80 HLT GSF SC HFEID; do
    HistToText $myf.root MYNA effSyst${myf}YError.csv
done