#!/bin/bash
cd /Users/edderioc/Desktop/T02D02-1/src || exit

file=files.log
n1 = "$(wc -l < "$file")"
>fa.txt
uniq -u "$file" > fa.txt

n2 = "$(wc -l < fa.txt)"
>fa.txt
FILE_PATH="$file"
> last_hash.txt
HASH_FILE="last_hash.txt"
CURRENT_HASH=$(sha256sum "$FILE_PATH" | awk '{ print $1 }')

if [[ "$CURRENT_HASH" != "$PREVIOUS_HASH" ]]; then
    echo "$CURRENT_HASH" > "$HASH_FILE"
fi

uniq -u last_hash.txt fa.txt
n3 = "$(( $(wc -l < last_hash.txt) - $(wc -l < fa.txt) ))"
echo $n1 $n2 $n3

rm last_hash.txt fa.txt