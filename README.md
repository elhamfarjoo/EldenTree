HI, I hope you all are doing well, 
This is the first version of my EldenTree mini project.



there are some points that need to be shared: 
A. Preparing the work environment:
1. I used "MSYS2" on windows alongside with "pacman" package manager to download necessary packages as following:
    1.1: pacman -Syu
    1.2: pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make mingw-w64-x86_64-gtest mingw-w64-x86_64-clang mingw-w64-x86_64-clang-tools-extra
2. I used VSCode and defined tasks.json and launch.json to handle tasks for building and launching Benchmark
3. I used standard C++17 library making sure my code is cross-platform


B. Software Architecture
1. there are 3 classes named CEldenTree, CLand and CGod with inheritacing classes CGodWind, CGodRain and so on.
2. I wrote a Benchmark.cpp under "test" directory for benchmarking purpose, so that, I first instanciate CEldenTree, then CGodWind, CGodRain, CGodThunder and CGodLightening and passed the Tree object to all of them. After that I instanciate different Lands named Atlantis, perspolise and so on. In the next step I Registered the lands with the Tree so that the EldenTree can route events to the respective land. In order to simulate different loads for each God, I assigned different number of lands to various Gods by God->AddLand() function. The final step is just to start threads of Lands, EldenTree, Gods, sleep for one second and stop the threads of Gods, EldenTree and Lands.
