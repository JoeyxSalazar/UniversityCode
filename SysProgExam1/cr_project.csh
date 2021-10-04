#!/bin/csh
set CP = cp
set MKDIR = mkdir
#set MKDIR = /usr/bin/mkdir        **************"usr/bin/mkdir: Command not found"
set PROJPATH = $PWD         #also known as current
set TOUCH = touch
#set TOUCH = /usr/local/touch
set PROJNAME = $argv[1]

$MKDIR $PROJNAME
cd $PROJPATH/$PROJNAME
#echo Navigated into dir
$MKDIR bin
#echo Created Bin
$MKDIR src
cd $PROJPATH/$PROJNAME/src
#echo Navigated into src directory
$TOUCH main.c
#echo Created main file
$CP $PROJPATH/cr_project.csh $PROJPATH/$PROJNAME
$CP $PROJPATH/build_project.csh $PROJPATH/$PROJNAME/bin
$CP $PROJPATH/myfind.c $PROJPATH/$PROJNAME/bin
#echo Copied script






