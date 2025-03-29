# Find Tins library
find_package(Tins REQUIRED)

# Find libpcap library
find_package(Pcap REQUIRED)

# Find pthread (typically available on most Unix-based systems)
find_package(Threads REQUIRED)

# Link them to your project
target_link_libraries(litgen-model Tins::Tins Pcap::Pcap Threads::Threads)

