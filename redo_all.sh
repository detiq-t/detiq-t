cd ImageIn
make clean
make
cd ../QtInterface/Widgets
rm -f *.*
cd ..
make clean
./config.pl clean
./config.pl
make
cd ../Applications/BasicApplication
make clean
./config.pl clean
./config.pl
make
cd ../../FiltrMe
make clean
./config.pl clean
./config.pl
make
cd ..
