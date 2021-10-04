#!/bin/csh
set PROJNAME = $argv[1]
set PROJPATH = $PWD
set GCCOPTS = "-c"
set LDOPTS = "-o"
set LD = /usr/bin/ld
set MV = /bin/mv
set STAT = /usr/bin/stat
set TOUCH = touch
set CP = cp
set MKDIR = mkdir


if (${#argv} < 1) then
        echo "No argument/path given"
        exit
endif

cd ..
set SRCPATH = $PWD/src 
cd $SRCPATH		#Gives us access to source files now
#echo $SRCPATH

foreach f (*.c)
	if(! -e $SRCPATH/$f) then			#file does not exist in the directory
		echo Error
		exit	
	endif

	set ofile = `basename -- "$f" .c`".o"
	set raw = `basename -- "$f" .c`
	if(! -e $SRCPATH/$ofile) then #if the compiled file does not exist
		gcc -c $SRCPATH/$f 
		echo Compiled $f
	else
		set ctime = `$STAT -f %Sm -t %Y%m%d%H%M%S $SRCPATH/$f`
		set otime = `$STAT -f %Sm -t %Y%m%d%H%M%S $SRCPATH/$ofile`
		if($ctime > $otime) then
			gcc -c $SRCPATH/$f
			echo Recompiling $f since last compile
		else
			echo $f has not been edited since last compiled
		endif
	endif
end

gcc *.o -lc -o $PROJNAME
mv $SRCPATH/$PROJNAME $PROJPATH/../bin

