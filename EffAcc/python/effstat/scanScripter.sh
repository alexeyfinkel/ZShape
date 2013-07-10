det=$1
param=$2
shift
shift
 
thisdir=${CMSSW_BASE}/src/ZShape/EffAcc/python/effstat
template=testProdZEfficiencySmeared_EFFStat_cfg.py
thatdir=${CMSSW_BASE}/src/ZShape/EffAcc/python/effstat


for numb in $@
    do
    #fabs=${numb/-/m}
    #cleannumb=${fabs/./_}
    name=Z2EcalEffStat${det}${param}_${numb}_cfg.py
    #name=EcalEffStat${det}${param}_${numb}_cfg.py
    #name=D6TEcalEffStat${det}${param}_${numb}_cfg.py
  #  name=P0EcalEffStat${det}${param}_${numb}_cfg.py
   # name=PT0EcalEffStat${det}${param}_${numb}_cfg.py
   # name=Q2EcalEffStat${det}${param}_${numb}_cfg.py



    cp $thisdir/$template $thatdir/$name
    sed -i "s/xxEFFSTRxx/$numb/g" $thatdir/$name
    sed -i "s/xxDETxx/$det/g" $thatdir/$name
    # sed -i "s/xxxx/$/g" $thatdir/$name
done
