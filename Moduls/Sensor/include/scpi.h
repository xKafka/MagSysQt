#ifndef SCPI_H
#define SCPI_H

#include <string>

class SCPI
{
    std::string m_data;

public:
    explicit SCPI(const char *data) noexcept : m_data(data)
    {}

    auto cmd() const { return m_data; }

    [[nodiscard]] inline auto size() const { return static_cast<unsigned long>(m_data.size()); }

    inline auto *data() { return reinterpret_cast<unsigned char *>(m_data.data()); }

    static SCPI identify() { return SCPI("*IDN?\n"); };

    static SCPI set_pins(const std::string &port)
    {
        std::string ret_val{ "ROUT:ENAB 1, (@" };

        ret_val += port + ")\n";

        return SCPI(ret_val.data());
    };

    static SCPI set_range(const std::string &port, const std::string &range)
    {
        std::string ret_val{ "ROUT:CHAN:RANG "};

        ret_val += range + ",(@" + port + ")\n";

        return SCPI(ret_val.data());
    };

    static SCPI set_polarity(const std::string &port, const std::string &polarity)
    {
        std::string ret_val{ "ROUT:CHAN:POL "};

        ret_val += polarity + ",(@" + port + ")\n";

        return SCPI(ret_val.data());
    };

    static SCPI set_sample_rate(const std::string &sample_rate)
    {
        std::string ret_val{ "ACQ:SRAT "};

        ret_val += sample_rate + "\n";

        return SCPI(ret_val.data());
    };

    static SCPI num_of_ret_vals(const std::string &ret_vals)
    {
        std::string ret_val{ "WAV:POIN "};

        ret_val += ret_vals + "\n";

        return SCPI(ret_val.data());
    };

    static SCPI measure_voltage(const std::string &port)
    {
        std::string ret_val{ "MEAS? (@"};

        ret_val += port + ")\n";

        return SCPI(ret_val.data());
    };

    static SCPI averaging(const std::string &how_much)
    {
        std::string ret_val{ "VOLT:AVER "};

        ret_val += how_much + "\n";

        return SCPI(ret_val.data());
    };

    static SCPI check_data()
    {
        return SCPI("WAV:DATA?\n");
    };

    static SCPI clear()
    {
        return SCPI("*CLS\n");
    };

    static SCPI reset()
    {
        return SCPI("*RST\n");
    };
    static SCPI single_shot()
    {
        return SCPI("DIG\n");
    };
};


#endif // SCPI_H
