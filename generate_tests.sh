#!/bin/bash

RED=$'\033[0;31m'
GREEN=$'\033[0;32m'
YELLOW=$'\033[0;33m'
RESET=$'\033[0m'

mkdir -p test_files

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
    ./ft_nm "$file" > test1;
    STATUS1=$?
    nm "$file" > test2;
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
        "./.obj/main.o")

for file in "${files[@]}"; do
    ./ft_nm "$file" > test1;
    nm "$file" > test2;
    if ! diff -q test1 test2 > /dev/null; then
        echo "$RED Test failed for $file $RESET"
        echo ""
    else
        echo "$GREEN Test passed for $file $RESET"
        echo ""
    fi
done