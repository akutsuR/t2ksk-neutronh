#!/bin/bash

TOPDIR=/disk02/usr6/rakutsu/t2k/compact/ncount/scripts
SUBMIT()
{
    mode=$1
    oscchan=$2
    seed=$3

    echo $mode $oscchan $seed
    iscript=mcdst.${mode}.${oscchan}.sh

# Make script 
##################################################################
/usr/bin/cat > $iscript << EOF
#!/bin/bash

top_dir=$TOPDIR
exe=\$top_dir/MkMCDist_single.csh
mode=$mode
oscchan=$oscchan
seed=$seed
\$exe \$mode \$oscchan \$seed
EOF
##################################################################
	/usr/bin/chmod +x $iscript
    qsub -eo -o /dev/null -q atmpd $iscript
    rm $iscript
}

iseed=27159
SUBMIT fhc numu_x_numu `expr $iseed + 768 \* 0`
SUBMIT fhc numu_x_nue `expr $iseed + 768 \* 1`
SUBMIT fhc nue_x_nue `expr $iseed + 768 \* 2`
SUBMIT fhc numubar_x_numubar `expr $iseed + 768 \* 3`
SUBMIT fhc numubar_x_nuebar `expr $iseed + 768 \* 4`
SUBMIT fhc nuebar_x_nuebar `expr $iseed + 768 \* 5`
SUBMIT rhc numu_x_numu `expr $iseed + 768 \* 6`
SUBMIT rhc numu_x_nue `expr $iseed + 768 \* 7`
SUBMIT rhc nue_x_nue `expr $iseed + 768 \* 8`
SUBMIT rhc numubar_x_numubar `expr $iseed + 768 \* 9`
SUBMIT rhc numubar_x_nuebar `expr $iseed + 768 \* 10`
SUBMIT rhc nuebar_x_nuebar `expr $iseed + 768 \* 11`
