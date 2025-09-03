#!/bin/bash

if [ "$#" -ne 1 ];then
    echo "U $0 <file_path>"
    exit 1
fi

log_file=$1
if [! -f "$file"];then
echo "Fnf: $file"
    exit 1
fi
n1 = $(wc -l < "$file")
n2 = $(awk '{print $1}' "$file" | sort -u | wc -l)
n3 = $(awk '{if ($4 != "sha256") print $3}' "$file" | sort -u | wc -l)
echo "$n1 $n2 $n3"