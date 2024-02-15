// Bimap for DNS
// 
// We use Bimap to implement a 1:1 mapping between the domain names
// and IP adresses (= Domain Name System, DNS).
// IP addresses are modelled as UUIDs (from wiki: Universally Unique Identifier (UUID) is a 128-bit 
// label used for information in computer systems).
// Domain names are modelled as standard strings.
// 
// Tobias Bilgeri, 28.1.2024
#pragma once
#include <iostream>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>


// typedefs for shorter notations
using DomainNames =   boost::bimaps::unordered_set_of<boost::bimaps::tagged<std::string, struct DomainName>>;
using IPs =           boost::bimaps::unordered_set_of<boost::bimaps::tagged<boost::uuids::uuid, struct IpAdress>>;
using DNS =           boost::bimap<DomainNames, IPs>;


// c. Create a function to print the contents of the DNS ‘database’.
void printDNS(const DNS& dns) {
    std::cout << "\n\nPrintDNS function called:\n";
    for (const auto& entry : dns) {
        std::cout << "\t" << entry.left << " <=> " << entry.right << "\n";
    }
}

int main() {

    // create DNS object
    DNS dns;

    // create example domain name 
    std::string example_domain = "www.helloworld.com";

    // create example IP
    boost::uuids::string_generator gen;
    std::string ip_uuid = "01234567-89ab-cdef-0123-456789abcdef";
    boost::uuids::uuid example_ip = gen(ip_uuid);

    // insert an example
    dns.insert(DNS::value_type(example_domain, example_ip));

    // find the example: left from right 
    auto it = dns.right.find(example_ip);
    if (it != dns.right.end()) {
        std::cout << "Found right from left: " << it->second << "\n";
    }

    // find the example: right from left 
    auto it2 = dns.left.find(example_domain);
    if (it2 != dns.left.end()) {
        std::cout << "Found right from left: " << it2->second << "\n";
    }

    printDNS(dns);

    return 0;
}