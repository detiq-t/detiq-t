#!/usr/bin/perl

$usage = "config.pl [clean]\n\t- delete the files created\n";

# FILE config.pl                                    
# This script prepare your makefile for compilation 
# with Qwt                                          

#Preparation
`rm Makefile 2> /dev/null`;
`qmake -project`;
`qmake`;

$pathLii = "";
$pathIncii = "";
$pathqwt = "";
$pathLqwt = "";
$qwtname = "";

if($#ARGV == 0)
{
  print $ARGV[1];

  if($ARGV[0] eq "clean")
  {
    `rm .config_*`
  }
  else
  {
    die "usage: $usage";
  }
}

elsif($#ARGV == -1)
{
  print "CREATION OF THE MAKEFILE\n\n";
  print "Scanning.......\n";

  #Search pathes for imagein
  #INCLUDES
  
  if(`ls -a .config_Iii 2> /dev/null` eq "")
  {
    `find /usr -name "ImageFileAbsFactory.h" >> .tmp 2> /dev/null`;
    `find /home -name "ImageFileAbsFactory.h" >> .tmp 2> /dev/null`;

    open TMP, ".tmp";
    open II, ">.config_Iii";


    while($line = <TMP>)
    {
      if($line =~ "(.*/)ImageFileAbsFactory.h")
      {
        $pathIncii = $1;
        print "Imaginein's header found: $pathIncii\n";
        print II $pathIncii;
        last;
      }
    }

    close II;
    close TMP;

    `rm .tmp`;
  }
  else
  {
    open II, ".config_Iii";

    print "get info in .config_Iii\n";

    $pathIncii = <II>;
    chomp($pathIncii);

    close II;
  }

  #INCLUDES
  if(`ls -a .config_Lii 2> /dev/null` eq "")
  {
    `find /usr -name "libimagein.a" >> .tmp 2> /dev/null`;
    `find /home -name "libimagein.a" >> .tmp 2> /dev/null`;

    open TMP, ".tmp";
    open II, ">.config_Lii";

    while($line = <TMP>)
    {
      if($line =~ "(.*/)libimagein.a")
      {
        $pathLii = $1;
        print II "$pathLii";

        print "libimagein.a found: $pathLii\n";
        last;
      }
    }

    close II;
    close TMP;

    `rm .tmp`;
  }
  else
  {
    open II, ".config_Lii";

    print "get info in .config_Lii\n";

    $pathLii = <II>;
    chomp($pathLii);

    close II;
  }

  #Search pathes for qwt
  if(`ls -a .config_Iqwt 2> /dev/null` eq "" or `ls -a .config_Lqwt 2> /dev/null` eq "")
  {
    `find /usr -name "*qwt*" > .tmp`;
    `rm .config_Lqwt 2> /dev/null`;
    `rm .config_Iqwt 2> /dev/null`;

    open TMP, ".tmp";
    open LQWT, ">.config_Lqwt";
    open IQWT, ">.config_Iqwt";

    $inc = 0;
    $l = 0;

    while($line = <TMP>)
    {
      if($line =~ "(.*/)qwt_plot.h" && !$inc)
      {
        $pathqwt = $1;

        print IQWT "$pathqwt\n";

        print "qwt found: $pathqwt\n";
        $inc = 1;
        $inc && $l && last;
      }
      if($line =~ "(.*/)lib(qwt.*).so" && !$l)
      {
        $pathLqwt = $1;
        $qwtname = $2;

        print LQWT "$pathLqwt\n$qwtname\n";

        print "qwt lib found: $pathLqwt\n";
        $l = 1;
        $inc && $l && last;
      }
      elsif($line =~ "(.*/)lib(qwt-+.*).so" && !$l)
      {
        $pathLqwt = $1;
        $qwtname = $2;

        print LQWT "$pathLqwt\n$qwtname\n";

        print "qwt lib found: $pathLqwt\n";
        $l = 1;
        $inc && $l && last;
      }
    }

    close TMP;
    close LQWT;
    close IQWT;

    `rm .tmp`;
  }
  else
  {
    open LQWT, ".config_Lqwt";
    open IQWT, ".config_Iqwt";

    print "get info in .config_Iqwt\n";
    $pathqwt = <IQWT>;
    chomp($pathqwt);

    print "get info in .config_Lqwt\n";
    $pathLqwt = <LQWT>;
    $qwtname = <LQWT>;
    chomp($pathLqwt);
    chomp($qwtname);

    close LQWT;
    close IQWT;
  }

  $pathLii eq ""  && die "Error: libimagein.a missing\n";
  $pathIncii eq ""  && die "Error: Imagein's headers missing\n";
  $pathLqwt eq ""    && die "Error: qwt lib unfound\n";
  $pathqwt eq ""    && die "Error: qwt header unfound\n";


  print "\nEditing Makefile.......\n";

  open MAKEFILE, "Makefile";
  open NMAKEFILE, ">.Makefile";

  $oldline = "";

  while($line = <MAKEFILE>)
  {
    if($oldline =~ "^LIBS")
    {
      if(!($line =~ "^LIBS"))
      {
        print NMAKEFILE "LIBS          += -L$pathLii -limagein\n";
        print "added line: LIBS          += -L$pathLii -limagein\n";
        print NMAKEFILE "LIBS          += -L$pathLqwt -lqwt -ljpeg -lpng\n";
        print "added line: LIBS          += -L$pathLqwt -lqwt -ljpeg -lpng\n";
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

  close NMAKEFILE;
  close MAKEFILE;

  `mv .Makefile Makefile`;
}

else
{
  die "usage: $usage";
}
