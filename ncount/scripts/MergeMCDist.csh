#!/bin/csh -f

set dst_name=tvarcor513us

set top_dir=/disk02/usr6/rakutsu/t2k/compact/ncount
source $top_dir/../envntag.csh

set exe_mrgExtra=$top_dir/bin/mrgExtraCC0PiNumuBrkDwn.exe

set out_dir=$top_dir/files/$dst_name
set input_file_dir=$out_dir

set isfhc=1
set outfile=$out_dir/fhc.mrgExtraCC0PiNumuBrkDwn.$dst_name.root
$exe_mrgExtra $isfhc\
		 $input_file_dir\
		 $outfile\
		 $dst_name

set isfhc=0
set outfile=$out_dir/rhc.mrgExtraCC0PiNumuBrkDwn.$dst_name.root
$exe_mrgExtra $isfhc\
		 $input_file_dir\
		 $outfile\
		 $dst_name
