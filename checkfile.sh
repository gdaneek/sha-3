#!/bin/bash

# Проверка количества аргументов
if [ "$#" -ne 2 ]; then
    echo "Использование: $0 <файл> <хэш-строка>"
    exit 1
fi

# Параметры
FILE=$1
HASH_STR=$2

# Вычисление длины хэш-строки, умноженной на 4
HASH_LENGTH=$(( ${#HASH_STR} * 4 ))
# Вызов программы sha-3tool с вычисленной длиной и файлом
COMPUTED_HASH=$($(find -iname sha3tool) $HASH_LENGTH $FILE)

# Сравнение хэшей
if [ "$COMPUTED_HASH" == "$HASH_STR" ]; then
    echo -e "FILE OK!\n"
else
    echo -e "FILE CORRUPTED!\n"
fi
