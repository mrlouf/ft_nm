#!/bin/bash

RED=$'\033[0;31m'
GREEN=$'\033[0;32m'
YELLOW=$'\033[0;33m'
RESET=$'\033[0m'

mkdir -p test_files
rm -fr ./test_files/*

################################
#       Incorrect files        #
################################

echo "Not an ELF" > test_files/text.txt

touch test_files/empty

dd if=/dev/urandom of=test_files/random.bin bs=1K count=1 2>/dev/null

printf "\x7FELF" > test_files/just_magic
printf "\x7FELX\x00" > test_files/wrong_magic

head -c 10 /bin/ls > test_files/truncated

mkdir -p test_files/directory

echo "secret" > test_files/no_read
chmod 000 test_files/no_read

ln -s /nonexistent test_files/broken_symlink

STATUS1=0
STATUS2=0

for file in test_files/*; do
    ./ft_nm "$file" > ./test_files/test1;
    STATUS1=$?
    nm "$file" > ./test_files/test2;
    STATUS2=$?
    if [ $STATUS1 -ne $STATUS2 ]; then
        echo "$RED Test failed for $file $RESET"
        echo ""
    else
        echo "$GREEN Test passed for $file $RESET"
        echo ""
    fi
done

echo ""
rm -fr ./test_files/*

################################
#       Regular files          #
################################

echo "Testing regular files..."
echo ""

files=("ft_nm"
        ".obj/main.o"
        ".obj/parse.o"
        ".obj/sort.o"
        ".obj/utils.o"
        ".obj/process.o"
        )

for file in "${files[@]}"; do
    ./ft_nm "$file" > ./test_files/test1;
    nm "$file" > ./test_files/test2;
    if ! diff -q ./test_files/test1 ./test_files/test2 > /dev/null; then
        echo "$RED Test failed for $file $RESET"
        echo ""
    else
        echo "$GREEN Test passed for $file $RESET"
        echo ""
    fi
done

echo ""
rm -fr ./test_files/*


################################
#       Reverse sort           #
################################

echo "Testing reverse sort (-r flag)..."
echo ""

files=("ft_nm"
        ".obj/main.o"
        ".obj/parse.o"
        ".obj/sort.o"
        ".obj/utils.o"
        ".obj/process.o"
        )

for file in "${files[@]}"; do
    ./ft_nm -r "$file" > ./test_files/test1;
    nm -r "$file" > ./test_files/test2;
    if ! diff -q ./test_files/test1 ./test_files/test2 > /dev/null; then
        echo "$RED Test failed for $file $RESET"
        echo ""
    else
        echo "$GREEN Test passed for $file $RESET"
        echo ""
    fi
done

echo ""
rm -fr ./test_files/*

################################
#            No sort           #
################################

echo "Testing no sort (-p flag)..."
echo ""

files=("ft_nm"
        ".obj/main.o"
        ".obj/parse.o"
        ".obj/sort.o"
        ".obj/utils.o"
        ".obj/process.o"
        )

for file in "${files[@]}"; do
    ./ft_nm -p "$file" > ./test_files/test1;
    nm -p "$file" > ./test_files/test2;
    if ! diff -q ./test_files/test1 ./test_files/test2 > /dev/null; then
        echo "$RED Test failed for $file $RESET"
        echo ""
    else
        echo "$GREEN Test passed for $file $RESET"
        echo ""
    fi
done

echo ""
rm -fr ./test_files/*

################################
#            All symbols       #
################################

echo "Testing all symbols (-a flag)..."
echo ""

files=("ft_nm"
        ".obj/main.o"
        ".obj/parse.o"
        ".obj/sort.o"
        ".obj/utils.o"
        ".obj/process.o"
        )

for file in "${files[@]}"; do
    ./ft_nm -a "$file" > ./test_files/test1;
    nm -a "$file" > ./test_files/test2;
    if ! diff -q ./test_files/test1 ./test_files/test2 > /dev/null; then
        echo "$RED Test failed for $file $RESET"
        echo ""
    else
        echo "$GREEN Test passed for $file $RESET"
        echo ""
    fi
done

echo ""
rm -fr ./test_files/*

################################
#         Global symbols       #
################################

echo "Testing global symbols (-g flag)..."
echo ""

files=("ft_nm"
        ".obj/main.o"
        ".obj/parse.o"
        ".obj/sort.o"
        ".obj/utils.o"
        ".obj/process.o"
        )

for file in "${files[@]}"; do
    ./ft_nm -g "$file" > ./test_files/test1;
    nm -g "$file" > ./test_files/test2;
    if ! diff -q ./test_files/test1 ./test_files/test2 > /dev/null; then
        echo "$RED Test failed for $file $RESET"
        echo ""
    else
        echo "$GREEN Test passed for $file $RESET"
        echo ""
    fi
done

echo ""
rm -fr ./test_files/*

################################
#        Undefined symbols     #
################################

echo "Testing undefined symbols (-u flag)..."
echo ""

files=("ft_nm"
        ".obj/main.o"
        ".obj/parse.o"
        ".obj/sort.o"
        ".obj/utils.o"
        ".obj/process.o"
        )

for file in "${files[@]}"; do
    ./ft_nm -u "$file" > ./test_files/test1;
    nm -u "$file" > ./test_files/test2;
    if ! diff -q ./test_files/test1 ./test_files/test2 > /dev/null; then
        echo "$RED Test failed for $file $RESET"
        echo ""
    else
        echo "$GREEN Test passed for $file $RESET"
        echo ""
    fi
done

echo ""
rm -fr ./test_files/*

################################
#        32-bit ELF tests      #
################################

echo "Creating 32-bit ELF test file..."

echo 'int main() { return 0; }' > ./test_files/test.c

gcc -m32 ./test_files/test.c -o ./test_files/elf32 2>/dev/null

if [ -f ./test_files/elf32 ]; then
    echo "$GREEN 32-bit ELF test file created successfully $RESET"
    echo ""
else
    echo "$RED Failed to create 32-bit ELF test file, skipping test... $RESET"
    exit 1
fi

echo "Testing 32-bit ELF file..."

./ft_nm ./test_files/elf32 > ./test_files/test1;
nm ./test_files/elf32 > ./test_files/test2;

if ! diff -q ./test_files/test1 ./test_files/test2 > /dev/null; then
    echo "$RED Test failed for 32-bit ELF file $RESET"
    echo ""
else
    echo "$GREEN Test passed for 32-bit ELF file $RESET"
    echo ""
fi

