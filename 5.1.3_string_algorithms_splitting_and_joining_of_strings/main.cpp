// Splitting & Joining Strings
// Tobias Bilgeri, 2024/01/25
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

template<typename T> using Vector = std::vector<T>;
template<typename K, typename V> using Map = std::map<K, V>;
using String = std::string;
using Date = boost::gregorian::date;

// ex. a. split & join
void splitAndJoin() {
    String s("1,2,3,4/5/9*56");
    Vector<String> res;

    // split string on seperators "/,*" & store in vector
    boost::split(
        res,
        s, 
        boost::is_any_of("/,*"));
    
    // join string using uniform seperator type "/"
    s = boost::join(
        res,
        "/");
    
    std::cout << s << '\n';  // "1/2/3/4/5/9/56"
}

// ex. b. convert string to boost::gregorian::date
Date stringToDate(const String& dateStr) {
    // requires string fmd "yyyy-mm-dd"
    Vector<String> parts;

    // split string on seperator "-" & store in vector
    boost::split(
        parts, 
        dateStr, 
        boost::is_any_of("-"));

    return Date(
        boost::lexical_cast<int>(parts[0]), // yyyy
        boost::lexical_cast<int>(parts[1]), // mm
        boost::lexical_cast<int>(parts[2])  // dd
    );
}

// ex. c. create map from string-encoded map.
Map<String, double> stringToMap(const String& str) {
    // String should represent map of format: {k1=v1, k2=v2, ...}

    Map<String, double> res;
    Vector<String> pairs;

    // Split string on "," and save parts to vector.
    // The parts represent Key-Value pairs.
    boost::split(
        pairs, 
        str, 
        boost::is_any_of(","));

    for (const String& kv_pair : pairs) {

        Vector<String> kv;

        // Split Key-Value pair.
        boost::split(
            kv, 
            kv_pair,
            boost::is_any_of("="));

        res[kv[0]] = boost::lexical_cast<double>(kv[1]);
    }
    return res;
}

int main() {

    // ex. a.
    splitAndJoin();

    // ex. b.
    String date_str("2015-12-31");
    auto date = stringToDate(date_str);
    std::cout << date << '\n';  // "2015-Dec-31" (boost' date types are printable directly)

    // ex. c.
    String map_str("port=23,pin=87,value=34.4");

    auto map = stringToMap(map_str);
    for (const auto& [key, value] : map) {
        std::cout << key << ": " << value << '\n';
    }

    return 0;
}