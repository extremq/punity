from PIL import Image
import os
from generate_code import *

# sprites.h
output_header = """#ifndef _SPRITES_
#define _SPRITES_

#include <cstdint>

#define _MAKE_ALPHA(name) name##_alpha
#define MAKE_ALPHA(name) _MAKE_ALPHA(name)
#define _MAKE_W(name) name##_w
#define MAKE_W(name) _MAKE_W(name)
#define _MAKE_H(name) name##_h
#define MAKE_H(name) _MAKE_H(name)
#define SPRITE(name, layer) name, MAKE_ALPHA(name), MAKE_H(name), MAKE_W(name), layer

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
    output_header += declare_sprite_extern(sprite_name, (width, height))
    print("\t\t- Extern complete!")

    # Write array in sprites.cpp
    print("\t\t- Making array...")
    output_code += write_sprite_array(sprite_name, pixels, (width, height))
    print("\t\t- Array complete!")

    print("\t- Finished processing '" + file_name + "'")

# Generate header
output_header += "\n}\n\n#endif"

with open(split_file + "sprites.h", "w") as file:
    file.write(output_header)

print("Wrote header to '" + split_file + "sprites.h" + "'")

# Generate cpp
output_code += "\n}"

with open(split_file + "sprites.cpp", "w") as file:
    file.write(output_code)

print("Wrote cpp to '" + split_file + "sprites.cpp" + "'")
