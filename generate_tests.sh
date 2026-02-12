#!/bin/bash

mkdir -p test_files

# Texte
echo "Not an ELF" > test_files/text.txt

# Vide
touch test_files/empty

# Binaire aléatoire
dd if=/dev/urandom of=test_files/random.bin bs=1K count=1 2>/dev/null

# Presque ELF
printf "\x7FELF" > test_files/just_magic
printf "\x7FELX\x00" > test_files/wrong_magic

# Trop petit
head -c 10 /bin/ls > test_files/truncated

# Répertoire (devrait être rejeté)
mkdir -p test_files/directory

# Fichier sans permission de lecture
echo "secret" > test_files/no_read
chmod 000 test_files/no_read

# Lien symbolique vers fichier inexistant
ln -s /nonexistent test_files/broken_symlink

echo "Test files created in test_files/"