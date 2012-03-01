#!/usr/bin/perl

print "\nCREATION OF THE MAKEFILE\n\nScanning.......\n";

# FILE config.pl                                    
# This script prepare your makefile for compilation 
# with Qwt                                          

#Preparation
`qmake -project`;
`qmake`;

#Search pathes for imagein
#INCLUDES
`find /usr -name "ImageFileAbsFactory.h" >> .tmp 2> /dev/null`;
`find /home -name "ImageFileAbsFactory.h" >> .tmp 2> /dev/null`;

open TMP, ".tmp";

$pathIncii = "";

while($line = <TMP>)
{
  if($line =~ "(.*/)ImageFileAbsFactory.h")
  {
    $pathIncii = $1;
    last;
  }
}

close TMP;

`rm .tmp`;

#INCLUDES
`find /usr -name "libimagein.a" >> .tmp 2> /dev/null`;
`find /home -name "libimagein.a" >> .tmp 2> /dev/null`;

open TMP, ".tmp";

$pathLii = "";

while($line = <TMP>)
{
  if($line =~ "(.*/)libimagein.a")
  {
    $pathLii = $1;
    last;
  }
}

close TMP;

`rm .tmp`;

#Search pathes for qwt
`find /usr -name "qwt*" > .tmp`;

open TMP, ".tmp";

$pathqwt = "";

while($line = <TMP>)
{
  if($line =~ "(.*/)qwt_plot.h")
  {
    $pathqwt = $1;
    last;
  }
}



close TMP;

`rm .tmp`;

$pathqwt eq ""    && die "Error: qwt unfound\n";
$pathIncii eq ""  && die "Error: Imagein's headers missing\n";
$pathLii eq ""  && die "Error: libimagein.a missing\n";

print "qwt found: $pathqwt\n";
print "Imaginein's header found: $pathIncii\n";
print "libimagein.a found: $pathLii\n\n";

print "Editing Makefile.......\n";

open MAKEFILE, "Makefile";
open NMAKEFILE, ">.Makefile";

$oldline = "";

while($line = <MAKEFILE>)
{
  if($line =~ "LIBS          += -lqwt\n" or $line =~ "INCPATH       += -I$pathqwt\n")
  {
    print "Error: Makefile already prepared\n";
    last;
  }

  if($oldline =~ "^LIBS")
  {
    if(!($line =~ "^LIBS"))
    {
      print NMAKEFILE "LIBS          += -L$pathLii -limagein\n";
      print "added line: LIBS          += -L$pathLii -limagein\n";
      print NMAKEFILE "LIBS          += -lqwt -ljpeg -lpng\n";
      print "added line: LIBS          += -lqwt -ljpeg -lpng\n";
    }
  }

  if($oldline =~ "^INCPATH")
  {
    if(!($line =~ "^INCPATH"))
    {
      print NMAKEFILE "INCPATH       += -I$pathIncii\n";
      print "added line: INCPATH       += -I$pathIncii\n";
      print NMAKEFILE "INCPATH       += -I$pathqwt\n";
      print "added line: INCPATH       += -I$pathqwt\n";
    }
  }

  print NMAKEFILE "$line";
  $oldline = $line;
}

`rm Makefile`;
`mv .Makefile Makefile`;
