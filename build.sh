mkdir bin
cd src/compiler
make
cp compiler ../../bin/
cd ../runtime
make
cp runtime ../../bin/

