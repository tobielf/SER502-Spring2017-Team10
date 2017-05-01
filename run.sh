cd bin
echo "Compiling test data1"
./compiler ../data/program1/code.ten code.asm
echo "Executing test data1"
./runtime ./code.asm
echo "Compiling test data2"
./compiler ../data/program2/code.ten code.asm
echo "Executing test data2"
./runtime ./code.asm
echo "Compiling test data3"
./compiler ../data/program3/code.ten code.asm
echo "Executing test data3"
./runtime ./code.asm
echo "Compiling test data4"
./compiler ../data/program4/code.ten code.asm
echo "Executing test data4"
./runtime ./code.asm
echo "Compiling test data5"
./compiler ../data/program5/code.ten code.asm
echo "Executing test data5"
./runtime ./code.asm
echo "Compiling test data6"
./compiler ../data/program6/code.ten code.asm
echo "Executing test data6"
./runtime ./code.asm
echo "Compiling test data7"
./compiler ../data/program7/code.ten code.asm
echo "Executing test data7"
./runtime ./code.asm
echo "Compiling test data8"
./compiler ../data/program8/code.ten code.asm
echo "Executing test data8"
./runtime ./code.asm
