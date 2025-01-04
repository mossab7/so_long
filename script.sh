#!/bin/bash

# Loop through all .c files in the current directory
for file in *.c; do
  # Check if the file is a regular .c file
  if [[ -f "$file" ]]; then
    # Use Vim in ex mode to apply the Stdheader command, save, and quit
    vim "$file" +":Stdheader" +":wq"
    echo "Applied Stdheader to $file"
  fi
done

