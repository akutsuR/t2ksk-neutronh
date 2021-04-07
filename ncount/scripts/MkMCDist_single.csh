#!/bin/csh -f

set numode=$1
set oscchan=$2
set seed=$3

set top_dir=/disk02/usr6/rakutsu/t2k/compact/ncount

set dst_name=tvarcor513us
source $top_dir/../envntag.csh

set exe_mkhist=$top_dir/bin/NeutronCount.exe
set in_top_dir=/home/rakutsu/disk2/t2k/neutron/sigmavar_fnnn/infiles/neut

# Trueth & reco. info about primary neutrino events
set in_fqmr_dir=$in_top_dir/fqmr/$numode/$oscchan
set in_fqmr=$in_fqmr_dir/'*'.t2kfcfvFQ.root

# Truth & reco. info about delayed neutrons
set in_ntag_dir=$in_top_dir/ntag513us/$numode/$oscchan
set in_ntag=$in_ntag_dir/'*'.ntagh.root

# Event-by-event XSec weights for priamry neutrino events 
set in_xsec_dir=$in_top_dir/wgtXSec/$numode/$oscchan
set in_xsec=$in_xsec_dir/'*'.wgtXsec.root

set out_file=$top_dir/files/$dst_name/$numode.$oscchan.$dst_name.root
		
$exe_mkhist -if "$in_fqmr"\
		    -in "$in_ntag"\
		    -ix "$in_xsec"\
		    -o $out_file\
		    -m $numode\
		    -c $oscchan\
			--rand $seed
