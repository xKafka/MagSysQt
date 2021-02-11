#ifndef GCODE_GENERATOR_H
#define GCODE_GENERATOR_H

#include <Utils/include/position.h>
#include <string>

namespace g_command_generator
{
    inline const std::string generate_position(const Position &position)
    {
        return "G1 X" + std::to_string(position.getX()) + " Y"  + std::to_string(position.getY()) + " Z"  + std::to_string(position.getZ()) + '\n';
    }
};

#endif // GCODE_GENERATOR_H
