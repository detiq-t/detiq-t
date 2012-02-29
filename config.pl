#!/usr/bin/perl

# FILE config.pl                                    
# This script prepare your makefile for compilation 
# with Qwt                                          
#
# Just follow the following sequence :
# qmake -project
# qmake
# ./config.pl
# make

`find /usr -name "qwt*" > .tmp`;

open TMP, ".tmp";

$path = "";

while($line = <TMP>)
{
  if($line =~ "(.*/)qwt_plot.h")
  {
    $path = $1;
    last;
  }
}



close TMP;

`rm .tmp`;

$path eq "" && die "Error: qwt unfound\n";
print "qwt found: $path\n";

open MAKEFILE, "Makefile";
open NMAKEFILE, ">.Makefile";

$oldline = "";

while($line = <MAKEFILE>)
{
  if($line =~ "LIBS          += -lqwt\n" or $line =~ "INCPATH       += -I$path\n")
  {
    print "Error: Makefile already prepared\n";
    last;
  }

  if($oldline =~ "^LIBS")
  {
    if(!($line =~ "^LIBS"))
    {
      print NMAKEFILE "LIBS          += -lqwt\n";
      print "added line: LIBS          += -lqwt\n";
    }
  }

  if($oldline =~ "^INCPATH")
  {
    if(!($line =~ "^INCPATH"))
    {
      print NMAKEFILE "INCPATH       += -I$path\n";
      print "added line: INCPATH       += -I$path\n";
    }
  }

  print NMAKEFILE "$line";
  $oldline = $line;
}

`rm Makefile`;
`mv .Makefile Makefile`;
