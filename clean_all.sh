cd ImageIn
make clean
cd ../QtInterface/Widgets
rm -f *.*
cd ..
make clean
./config.pl clean
cd ../Applications/BasicApplication
make clean
./config.pl clean
cd ../../FiltrMe
make clean
./config.pl clean
cd ..
