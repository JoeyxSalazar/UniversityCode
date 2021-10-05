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
set GREP = /usr/bin/grep
set loc = $PWD
set SED = /usr/bin/sed 

if(${#argv} < 1) then
	echo No arguments provided
endif

if(${#argv} == 1) then
	switch ($argv[1])
	case -c:
		echo Clearing garbage directory
		$RM $gardir/*
		touch index.txt
		breaksw
	endsw
else if(${#argv} > 1) then
	if(! -f $argv[2]) then
			echo "$argv[2] does not exist or is not regular"
			exit
	endif
	switch ($argv[1])
	case -d:
		if(! -e $gardir/$argv[2]) then
			echo cannot return because it does not exist in garbage directory
			exit
		else
			set line = `$GREP $gardir/index.txt -e "$argv[2]"`
			if(-e ${line}) then
				echo Cannot overwite, file exists already 
			else
				$CP $gardir/$argv[2] ${line[2]}  #Copy back to orignal
				$RM $gardir/$argv[2]				#remove from garbage
	        	$SED  -i .bak '/$argv[2]/d' $index #remove from index file
	        	echo File has been untrashed
				exit
		endif
	case -f:
		if(! -e $gardir/$argv[2]) then
			echo cannot return because it does not exist in garbage directory
			exit
		else
			$CP $gardir/$argv[2] ${line[2]}  #Copy back to orignal
			$RM $gardir/$argv[2]				#remove from garbage
	        $SED  -i .bak '/$argv[2]/d' $index #remove from index file
	        echo File has been untrashed
			exit

	default:
		echo Do not understand "command" given
	endsw
endif
