def declare_extern(name, size):
    # Creates 4 declarations, one for buffer, one for alpha and two for sizes
    return f"\textern uint16_t const {name} [{size[0]} * {size[1]}];\n" \
            f"\textern bool const {name}_alpha [{size[0]} * {size[1]}];\n" \
            f"\textern uint16_t const {name}_w;\n" \
            f"\textern uint16_t const {name}_h;\n"
        

def write_sprite(name, pixels, size):
    # Returns a string with the buffer and alpha arrays
    buffer_code = f"\tuint16_t const {name} [{size[0]} * {size[1]}] = {{"
    alpha_code = f"\tbool const {name}_alpha [{size[0]} * {size[1]}] = {{"
    sprite_width = f"\tuint16_t const {name}_w = {size[0]};\n"
    sprite_height = f"\tuint16_t const {name}_h = {size[1]};\n"

    for pixel in pixels:
        buffer_code += f" {'{0:#x}'.format(rgb888_to_rgb565(pixel[0], pixel[1], pixel[2]))},"
        alpha_code += f" {'true' if pixel[3] != 0 else 'false'},"

    buffer_code = buffer_code[:-1] + " };\n"
    alpha_code = alpha_code[:-1] + " };\n"
    return buffer_code + alpha_code + sprite_width + sprite_height

def rgb888_to_rgb565(r, g, b):
    return ((r >> 3) << 11) + ((g >> 2) << 5) + (b >> 3)