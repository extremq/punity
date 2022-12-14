from PIL import Image
import os
from generate_code import *

# sprites.h
output_header = """#ifndef _SPRITES_
#define _SPRITES_

#include <cstdint>

namespace Game::Sprites {
    
"""

# sprites.cpp
output_code = """#include "sprites.h"

namespace Game::Sprites {

"""

split_file = __file__.split('/')
split_file = '/'.join(split_file[:-1]) + '/'

# Go through all files inside sprites directory
sprite_directory = split_file + "Sprites/"

print("Directory: " + sprite_directory)
print("Got files: " + str(sorted(os.listdir(sprite_directory))))
print("Starting to generate C++ headers...")

for file_name in sorted(os.listdir(sprite_directory)):
    print("\t- Processing '" + file_name + "'")

    if not file_name.endswith(".png"):
        continue

    file_path = sprite_directory + file_name
    sprite_name = file_name[:-4]

    # Open image and get all pixel data in a list
    image = Image.open(file_path)
    pixels = list(image.getdata())

    width, height = image.size

    # Create extern in sprites.h
    print("\t\t- Making extern...")
    output_header += declare_extern(sprite_name, (width, height))
    print("\t\t- Extern complete!")

    # Write array in sprites.cpp
    print("\t\t- Making array...")
    output_code += write_sprite(sprite_name, pixels, (width, height))
    print("\t\t- Array complete!")

    print("\t- Finished processing '" + file_name + "'")

# Generate header
output_header += "\n}\n\n#endif"
output_header_file = open(split_file + "sprites.h", "w")
output_header_file.write(output_header)

print("Wrote header to '" + split_file + "sprites.h" + "'")

# Generate cpp
output_code += "\n}"
output_code_file = open(split_file + "sprites.cpp", "w")
output_code_file.write(output_code)

print("Wrote cpp to '" + split_file + "sprites.cpp" + "'")
