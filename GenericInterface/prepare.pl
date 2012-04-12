#!/usr/bin/perl

`qmake -project`;
open PRO, "GenericInterface.pro";
open NPRO, ">NGenericInterface.pro";

$wr = 0;

while($ligne = <PRO>)
{
  if($w)
  {
    print NPRO $ligne;
  }

  if($ligne =~ /TEMPLATE/)
  {
    print NPRO "TEMPLATE = lib\nLIBS += -lqwt -limagein -lpng -ljpeg\n";
    $w = 1;
  }
}

close PRO;
close NPRO;

`mv NGenericInterface.pro GenericInterface.pro`;
