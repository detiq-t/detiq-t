#!/usr/bin/perl

`qmake -project`;
open PRO, "BitPlane.pro";
open NPRO, ">NBitPlane.pro";

$wr = 0;

while($ligne = <PRO>)
{
  if($w)
  {
    print NPRO $ligne;
  }

  if($ligne =~ /TEMPLATE/)
  {
    print NPRO "TEMPLATE = app\nLIBS += -lqwt -limagein -lpng -ljpeg -lGenericInterface\n";
    $w = 1;
  }
}

close PRO;
close NPRO;

`mv NBitPlane.pro BitPlane.pro`;
