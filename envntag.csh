source /usr/local/sklib_gcc4.8.5/cshenv_gcc4.8.5_skofl_16c+atmpd_16c
setenv ANAT2KSK_ROOT /disk02/usr6/rakutsu/t2k/compact/anat2ksk

if ( $?LD_LIBRARY_PATH ) then
	setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:$ANAT2KSK_ROOT/lib
else
	setenv LD_LIBRARY_PATH $ANAT2KSK_ROOT/lib
endif

setenv PATH /usr/local/texlive/2020/bin/x86_64-linux:${PATH}
