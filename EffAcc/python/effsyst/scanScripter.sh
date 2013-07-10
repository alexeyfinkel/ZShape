zdef=$1
param=$2
shift
shift
 
thisdir=${CMSSW_BASE}/src/ZShape/EffAcc/python/effsyst
template=testProdZEfficiencySmeared_EFFSyst_cfg.py
thatdir=${CMSSW_BASE}/src/ZShape/EffAcc/python/effsyst




for numb in $@
    do
    #fabs=${numb/-/m}
    #cleannumb=${fabs/./_}
#    name=EcalEffSyst${zdef}${param}_${numb}_cfg.py
# name=Z2EcalEffSyst${zdef}${param}_${numb}_cfg.py
#   name=D6TEcalEffSyst${zdef}${param}_${numb}_cfg.py
  name=P0EcalEffSyst${zdef}${param}_${numb}_cfg.py
#    name=PT0EcalEffSyst${zdef}${param}_${numb}_cfg.py
   # name=Q2EcalEffSyst${zdef}${param}_${numb}_cfg.py
    cp $thisdir/$template $thatdir/$name
    sed -i "s/xxEFFSTRxx/$numb/g" $thatdir/$name
    sed -i "s/xxZDEFxx/$zdef/g" $thatdir/$name
    # sed -i "s/xxxx/$/g" $thatdir/$name
done
