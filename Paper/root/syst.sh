#!/bin/sh

for myf in WP95 WP80 HLT GSF SC; do
    HistToText $myf.root MYNA effSyst${myf}PtError.csv
done