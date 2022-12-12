from PIL import Image
import os
from generate_code import *

print("RUN THIS SCRIPT FROM SAME FOLDER AS FILE.")

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

# Go through all files inside sprites directory
sprite_directory = "Sprites/"
for file_name in os.listdir(sprite_directory):
    if not file_name.endswith(".png"):
        continue

    file_path = sprite_directory + file_name
    sprite_name = file_name[:-4]

    # Open image and get all pixel data in a list
    image = Image.open(file_path)
    pixels = list(image.getdata())

    width, height = image.size

    # Create extern in sprites.h
    output_header += declare_extern(sprite_name, (width, height))

    # Write array in sprites.cpp
    output_code += write_sprite(sprite_name, pixels, (width, height))

# Generate header
output_header += "\n}\n\n#endif"
output_header_file = open("sprites.h", "w")
output_header_file.write(output_header)

# Generate cpp
output_code += "\n}"
output_code_file = open("sprites.cpp", "w")
output_code_file.write(output_code)

print("Done!")
