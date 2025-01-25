#ifndef _INDAT_PARSER_HPP_
#define _INDAT_PARSER_HPP_

#include <exception>
#include <fstream>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace indat {

class Parser {
  private:
    std::unordered_map<std::string, std::vector<std::string>> m_params;

    std::vector<std::string> split(std::string& s,
                                   const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            if (token.length() > 0)
                tokens.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        tokens.push_back(s);
        return tokens;
    }

    std::pair<std::string, std::string>
    split_name_value(std::string& s, const std::string& delimiter) {
        size_t pos = 0;
        std::string token;
        std::pair<std::string, std::string> ret;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            if (token.length() > 0) {
                ret.first = token;
                break;
            }
        }
        ret.second = s;
        return ret;
    }

    void parse_file(const std::string fname) {
        std::ifstream file(fname);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + fname);
        }
        std::string line;
        while (std::getline(file, line)) {
            auto [name, value] = split_name_value(line, " ");
            if (name.empty())
                continue;
            if (name[0] == '#')
                continue;
            m_params[name] = split(value, " ");
        }
    }

  public:
    explicit Parser(const std::string fname) { parse_file(fname); }

    template <typename T> static constexpr bool is_supported_type() {
        return std::is_floating_point<T>::value || std::is_integral<T>::value ||
               std::is_same<T, std::string>::value ||
               std::is_same<T, std::vector<std::string>>::value ||
               std::is_same<T, std::vector<double>>::value ||
               std::is_same<T, std::vector<int>>::value;
    }

    template <typename T> std::optional<T> get(const std::string& param) const {
        static_assert(is_supported_type<T>(), "Unsupported type");
        if (m_params.find(param) == m_params.end()) {
            return {};
        }

        if constexpr (std::is_same<T, std::vector<std::string>>::value) {
            return m_params.at(param);
        } else if constexpr (std::is_same<T, std::vector<int>>::value) {
            std::vector<int> ret;
            for (auto i : m_params.at(param)) {
                ret.push_back(std::stoi(i));
            }
            return ret;
        } else if constexpr (std::is_same<T, std::vector<double>>::value) {
            std::vector<double> ret;
            for (auto i : m_params.at(param)) {
                ret.push_back(std::stod(i));
            }
            return ret;
        } else {
            if (m_params.at(param).size() != 1) {
                throw std::runtime_error(
                    "Parameter has more or less than one value: " + param);
            }
            if constexpr (std::is_floating_point<T>::value) {
                return std::stod(m_params.at(param)[0]);
            } else if constexpr (std::is_integral<T>::value) {
                return std::stoll(m_params.at(param)[0]);
            } else if constexpr (std::is_same<T, std::string>::value) {
                return m_params.at(param)[0];
            }
        }
    }
};

} // namespace indat

#endif // _INDAT_PARSER_HPP_