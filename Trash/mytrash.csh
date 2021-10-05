#!/bin/csh

echo you entered ${#argv} arguments

if (${#argv} == 0) then
	echo No arguments provided
	exit
endif

# set some globals
set gardir = ~/garbage
set index = ~/garbage/index.txt
set CP = /bin/cp
set RM = /bin/rm
set loc = $PWD


# check if garbage dir exists
if (! -d $gardir) then
	echo "$gardir does not exist"
endif


if (${#argv} == 1) then #This establishes that the user only wants to delete if it does not already exist
	switch ($argv[1])
	case -l:
		echo Printing files in garbage bin
		ls $gardir
		cat $index
		exit
	default:
		#Check and see if the file is regular or exists
		if(! -f $argv[1]) then
			echo "$argv[1] does not exist or is not regular"
			exit
		endif
		#Check and see if the file is in garbage already
		if(-e ${gardir}/${argv[1]:t}) then
			echo "argv[1] exists in garbage"
			exit
		endif
		#move to garbage
		echo "$CP $argv[1] $gardir"
		echo "$RM $argv[1]"
		echo "$argv[1] $loc" >> ${gardir}/index.txt
		echo copied location to index
		$CP $argv[1] $gardir
		$RM $argv[1]
	endsw	
else if(${#argv} > 1) then
	switch ($argv[1])
	case -f:
		#move to garbage no matter what
		echo "$CP $argv[1] $gardir"
		echo "$RM $argv[1]"
		echo "$argv[1] $loc" >> ${gardir}/index.txt
		echo copied location to index
		$CP $argv[1] $gardir
		$RM $argv[1]
		
	default:
		echo Do not understand argument

endif

