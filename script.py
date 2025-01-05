import os

def duplicate_and_add_bonus(directory):
    # Get all files in the directory
    for filename in os.listdir(directory):
        # Check if the file is a C file
        if filename.endswith(".h"):
            # Create the new file name with '_bonus' before the extension
            new_filename = filename.replace(".h", "_bonus.h")
            original_file = os.path.join(directory, filename)
            new_file = os.path.join(directory, new_filename)

            # Copy the content from the original file to the new file
            with open(original_file, 'r') as src_file:
                content = src_file.read()

            with open(new_file, 'w') as dest_file:
                dest_file.write(content)

            print(f"Duplicated {filename} to {new_filename}")

# Replace this with your directory path
directory_path = "/goinfre/mbouhia/so_long"
duplicate_and_add_bonus(directory_path)
