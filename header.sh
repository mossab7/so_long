#!/bin/bash

# Ensure that the script is run in the correct directory
if [ ! -d "$1" ]; then
  echo "Directory $1 not found."
  exit 1
fi

# Change to the specified directory
cd "$1" || exit

# Loop through all .c files in the directory
for file in *.c; do
  if [ -f "$file" ]; then
    echo "Applying Stdheader to $file"
    # Open the file with Vim and run the Stdheader command
    vim -c 'Stdheader' -c 'wq' "$file"
  fi
done

echo "Stdheader applied to all .c files in $1"
