from PIL import Image
import os
from generate_code import *

# sprites.h
output_header = """#ifndef _MAPS_
#define _MAPS_

#include <cstdint>

enum Tile {
    EMPTY,
    WALL,
    ENEMY,
    PORTAL,
    PLAYER,
    BOX,
    PRIZE
};

namespace Game::Maps {
    
"""

# sprites.cpp
output_code = """#include "maps.h"

namespace Game::Maps {

"""

split_file = __file__.split('/')
split_file = '/'.join(split_file[:-1]) + '/'

# Go through all files inside sprites directory
map_directory = split_file + "Maps/"

print("Directory: " + map_directory)
print("Got files: " + str(sorted(os.listdir(map_directory))))
print("Starting to generate C++ headers...")

for file_name in sorted(os.listdir(map_directory)):
    print("\t- Processing '" + file_name + "'")

    if not file_name.endswith(".png"):
        continue

    file_path = map_directory + file_name
    sprite_name = file_name[:-4]

    # Open image and get all pixel data in a list
    image = Image.open(file_path)
    pixels = list(image.getdata())

    width, height = image.size

    if width != height and width != 12:
        print(f"\t- Image has wrong sizes!")
        continue

    # Create extern in map.h
    print("\t\t- Making extern...")
    output_header += declare_map_extern(sprite_name)
    print("\t\t- Extern complete!")

    # Write array in map.cpp
    print("\t\t- Making array...")
    output_code += write_map_array(sprite_name, pixels)
    print("\t\t- Array complete!")

    print("\t- Finished processing '" + file_name + "'")

# Generate header
output_header += "\n}\n\n#endif"

with open(split_file + "maps.h", "w") as file:
    file.write(output_header)

print("Wrote header to '" + split_file + "maps.h" + "'")

# Generate cpp
output_code += "\n}"

with open(split_file + "maps.cpp", "w") as file:
    file.write(output_code)

print("Wrote cpp to '" + split_file + "maps.cpp" + "'")
