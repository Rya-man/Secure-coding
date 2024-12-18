mkdir src
cd src
touch main.cpp
mkdir Authentication
cd Authentication
touch AuthManager.cpp AuthManager.h AuthUtils.cpp AuthUtils.h
cd ..

mkdir Hashing
cd Hashing
touch Hasher.cpp Hasher.h
cd ..
mkdir FileIO
cd FileIO
touch FileManager.cpp FileManager.h
cd ..
mkdir Models
cd Models
touch User.cpp User.h
cd ..
mkdir Utils
cd Utils
touch Logger.cpp Logger.h TimeUtils.cpp TimeUtils.h
cd ..
mkdir Config
cd Config
touch Config.cpp Config.h
cd ..



cd ..




mkdir include


mkdir tests
cd tests
touch AuthenticationTests.cpp HashingTests.cpp FileIOTests.cpp
cd ..

mkdir lib



mkdir data
cd data
touch users.csv lockout.csv
cd ..



mkdir docs
cd docs
touch README.md DESIGN.md
cd ..

mkdir build



mkdir scripts
cd scripts
touch build.sh run_tests.sh
cd ..


touch .gitignore CMakeLists.txt