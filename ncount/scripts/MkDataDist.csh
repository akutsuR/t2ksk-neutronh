#!/bin/csh -f

set top_dir=/disk02/usr6/rakutsu/t2k/compact/ncount
source $top_dir/../envntag.csh

set exe_mkhist=$top_dir/bin/NeutronCount.exe
set in_top_dir=/disk02/usr6/rakutsu/t2k/chkqual/infiles

#set dst_name=2019May_fcfv
set dst_name=2019May_1rmu

foreach numode (fhc rhc)
set oscchan=data
	set in_fqmr_dir=$in_top_dir/fq_root_2018Jun
	set in_fqmr=$in_fqmr_dir/'*'.root
	
	set in_ntag_dir=$in_top_dir/ntag_root_2019May
	set in_ntag=$in_ntag_dir/'*'.root

	set out_file=$top_dir/files/$dst_name/$numode.$oscchan.$dst_name.root

if ( $dst_name == 2019_fcfv ) then
	set isFCFVOnly=1
else
	set isFCFVOnly=0
endif

$exe_mkhist -if "$in_fqmr"\
		    -in "$in_ntag"\
		    -o $out_file\
		    -m $numode\
		    -c $oscchan\
			--FCFVonly $isFCFVOnly
/usr/bin/sleep 1
echo " "
end
