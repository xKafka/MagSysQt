#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <QMetaType>

class Position
{
    double m_x{}, m_y{}, m_z{};

public:
    Position() = default;

    Position(double x, double y, double z)
        : m_x{ x },
          m_y{ y },
          m_z{ z }
    { }

    enum Axis
    {
        X = 0,
        Y,
        Z,
        Size
    };

    [[nodiscard]] std::string dump() const
    {
        std::string ret_val;

        ret_val += '{' + std::to_string(getX()) + '}';
        ret_val += '{' + std::to_string(getY()) + '}';
        ret_val += '{' + std::to_string(getZ()) + '}';

        return ret_val;
    }

    double getX() const { return m_x; }
    double getY() const { return m_y; }
    double getZ() const { return m_z; }


    Position &setX(double val) { m_x = val; return *this; }
    Position &setY(double val) { m_y = val; return *this; }
    Position &setZ(double val) { m_z = val; return *this; }

    inline Position &operator+=(const double other)
    {
        setX(getX() + other);
        setY(getY() + other);
        setZ(getZ() + other);

        return *this;
    }

    Position &operator+=(const Position &other)
    {
        setX(getX() + other.getX());
        setY(getY() + other.getY());
        setZ(getZ() + other.getZ());

        return *this;
    }
};

inline Position operator+(const Position &left, const Position &right)
{
    return { left.getX() + right.getY(), left.getY() + right.getY(), left.getZ() + right.getZ() };
}

inline Position operator-(const Position &left, const Position &right)
{
    return { left.getX() - right.getY(), left.getY() - right.getY(), left.getZ() - right.getZ() };
}

inline bool operator==(const Position &left, const Position &right)
{
    return left.getX() == right.getY() &&  left.getY() == right.getY() && left.getZ() == right.getZ();
}

inline bool operator!=(const Position &left, const Position &right)
{
    return left.getX() != right.getY() ||  left.getY() != right.getY() || left.getZ() != right.getZ();
}

inline bool operator>(const Position &left, const Position &right)
{
    return left.getX() > right.getY() &&  left.getY() > right.getY() && left.getZ() > right.getZ();
}

inline bool operator<(const Position &left, const Position &right)
{
    return left.getX() < right.getY() &&  left.getY() < right.getY() && left.getZ() < right.getZ();
}

Q_DECLARE_METATYPE(Position)


#endif // POSITION_H
