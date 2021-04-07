#!/bin/csh -f

set top_dir=/disk02/usr6/rakutsu/t2k/compact/ncount

set dst_name=tvarcor513us
source $top_dir/../envntag.csh
set exe_meas=$top_dir/bin/measureNeutrons.exe

set sys_dir=/disk02/usr6/rakutsu/t2k/neutron/totsys_tentative/outputs 

#set use_rndm_err=1
set use_rndm_err=0

set mc_dst=tvarcor513us
set da_dst=2019May_1rmu
set in_mc_fhc=$top_dir/files/$mc_dst/fhc.mrgExtraCC0PiNumuBrkDwn.$mc_dst.root
set in_mc_rhc=$top_dir/files/$mc_dst/rhc.mrgExtraCC0PiNumuBrkDwn.$mc_dst.root
set in_syserr=$sys_dir/tageff_totalsystematics.root
set in_da_fhc=$top_dir/files/$da_dst/fhc.data.$da_dst.root
set in_da_rhc=$top_dir/files/$da_dst/rhc.data.$da_dst.root

set out_file=$top_dir/files/nmeas/nmeas_results.2019May.rndmthrwstaterr.root
if ( $use_rndm_err == 0 ) then
	set out_file=$top_dir/files/nmeas/nmeas_results.2019May.conststaterr.root
endif

$exe_meas -i_mc_fhc $in_mc_fhc\
		  -i_mc_rhc $in_mc_rhc\
		  -i_syserr $in_syserr\
		  -i_da_fhc $in_da_fhc\
		  -i_da_rhc $in_da_rhc\
		  -o $out_file\
		  -rndmsd 27847\
		  -nthrw 1000000\
		  --RndmThrwStatErr $use_rndm_err
