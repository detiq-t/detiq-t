#!/usr/bin/perl

`qmake -project`;
open PRO, "FiltrMe.pro";
open NPRO, ">NFiltrMe.pro";

$wr = 0;

while($ligne = <PRO>)
{
  if($w)
  {
    print NPRO $ligne;
  }

  if($ligne =~ /TEMPLATE/)
  {
    print NPRO "TEMPLATE = app\nLIBS += -lqwt -limagein -lpng -ljpeg -lGenericInterface\nQT += xml\n";
    $w = 1;
  }
}

close PRO;
close NPRO;

`mv NFiltrMe.pro FiltrMe.pro`;

