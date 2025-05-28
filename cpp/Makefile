CXX=g++
CXXWIN=x86_64-w64-mingw32-g++

CXXFLAGS=-std=c++20 -Wall

LIBPLAYTRON_SDK=files/linux-x64/bin/libplaytron_sdk.so
BIN_DIR=./files/linux-x64/bin
WIN_LIB=files/win-x64/lib
WIN_BUILD=build/win-x64/bin

.PHONY: examples-attestation-linux-x64
examples-attestation-linux-x64: build/linux-x64/bin/attestation
build/linux-x64/bin/attestation: examples/attestation/main.cxx
	mkdir -p build/linux-x64/bin
	$(CXX) $(CXXFLAGS) -o build/linux-x64/bin/attestation -Iinclude -Ivendor/json/include -L$(BIN_DIR) -lplaytron_sdk -lcurl examples/attestation/main.cxx
	cp $(LIBPLAYTRON_SDK) build/linux-x64/bin/

.PHONY: examples-web3-linux-x64
examples-web3-linux-x64: build/linux-x64/bin/web3
build/linux-x64/bin/web3: examples/web3/main.cxx
	mkdir -p build/linux-x64/bin
	$(CXX) $(CXXFLAGS) -o build/linux-x64/bin/web3 -Iinclude -Ivendor/json/include -L$(BIN_DIR) -lplaytron_sdk -lcurl examples/web3/main.cxx
	cp $(LIBPLAYTRON_SDK) build/linux-x64/bin/

.PHONY: examples-attestation-win-x64
examples-attestation-win-x64: build/win-x64/bin/attestation.exe
build/win-x64/bin/attestation.exe: examples/attestation/main.cxx
	mkdir -p build/obj
	mkdir -p build/win-x64/bin
	$(CXXWIN) $(CXXFLAGS) -c -o build/obj/attestation.o -Iinclude -Ivendor/json/include -Ivendor/curl/include examples/attestation/main.cxx
	$(CXXWIN) $(CXXFLAGS) -o build/win-x64/bin/attestation.exe -Lvendor/curl/lib-win-x64 -Wl,--whole-archive -l:libcurl.dll.a -l:libwinpthread.a -L$(WIN_LIB) -l:playtron_sdk.dll.a -Wl,--no-whole-archive -static-libstdc++ -static-libgcc build/obj/attestation.o
	cp ./vendor/curl/bin-win-x64/libcurl-x64.dll $(WIN_BUILD)
	cp ./files/win-x64/bin/playtron_sdk.dll $(WIN_BUILD)

.PHONY: examples-web3-win-x64
examples-web3-win-x64: build/win-x64/bin/web3.exe
build/win-x64/bin/web3.exe: examples/web3/main.cxx
	mkdir -p build/obj
	mkdir -p build/win-x64/bin
	$(CXXWIN) $(CXXFLAGS) -c -o build/obj/web3.o -Iinclude -Ivendor/json/include -Ivendor/curl/include examples/web3/main.cxx
	$(CXXWIN) $(CXXFLAGS) -o build/win-x64/bin/web3.exe -Lvendor/curl/lib-win-x64 -Wl,--whole-archive -l:libcurl.dll.a -l:libwinpthread.a -L$(WIN_LIB) -l:playtron_sdk.dll.a -Wl,--no-whole-archive -static-libstdc++ -static-libgcc build/obj/web3.o
	cp ./vendor/curl/bin-win-x64/libcurl-x64.dll $(WIN_LIB)

.PHONY: clean
clean:
	rm -rf .cache
	rm -rf build
	rm -rf dist
	rm -f *.o