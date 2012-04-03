#!/usr/bin/perl

`qmake -project`;
open PRO, "QtInterface.pro";
open NPRO, ">NQtInterface.pro";

$wr = 0;

while($ligne = <PRO>)
{
  if($w)
  {
    print NPRO $ligne;
  }

  if($ligne =~ /TEMPLATE/)
  {
    print NPRO "TEMPLATE = lib\nCONFIG += staticlib\nLIBS += -lqwt -limagein -lpng -ljpeg\n";
    $w = 1;
  }
}

close PRO;
close NPRO;

`mv NQtInterface.pro QtInterface.pro`;
