# Playtron GameOS C++ SDK

Welcome to the official **Playtron GameOS C++ SDK** — a native C++ interface for building applications that integrate with the Playtron runtime.

This SDK supports both **Linux** and **Windows (via Wine/Proton)** and includes full examples for attestation, web3 signing, and more.

## Table of Contents

- [Features](#features)
- [Requirements for Examples](#requirements-for-examples)
- [SDK Installation](#sdk-installation)
- [Examples](#examples)
  - [Attestation](#attestation)
  - [Web3](#web3)
- [Building and Testing Examples](#building-and-testing-examples)
  - [Attestation - Linux](#linux-1)
  - [Attestation - Windows](#windows-1)
  - [Web3 - Linux](#linux-2)
  - [Web3 - Windows](#windows-2)
- [API Reference](#-api-reference)
- [Exceptions](#-exceptions)
- [License](#license)

---

## Features

- Remote attestation via TPM
- Message signing and transaction execution
- Cross-platform support (Linux + Wine/Proton on Windows)
- Clean, minimal examples in C++

---

## Requirements

- GameOS Beta 1.1+ (provides required native libraries)

### Linux
- `g++` with C++20 support
- `make`

### Windows (Cross-compilation from Linux)
- `x86_64-w64-mingw32-g++`
- Wine or Proton (for testing)

---

## SDK Installation

To use the SDK, follow these steps:

### Linux

- Include the [libplaytron_sdk.so](./files/linux-x64/bin/libplaytron_sdk.so) file in your compilation
- If compiling manually, then add this to your command `-Ldirectory/to/sdk/file -lplaytron_sdk`

### Windows

- Include the [playtron_sdk.dll.a](./files/win-x64/lib/libplaytron_sdk.dll.a) lib file in your compilation
- If compiling manually, then add this to your command `-Ldirectory/to/sdk/file -l:playtron_sdk.dll.a`
- Ensure [playtron_sdk.dll](./files/win-x64/bin/libplaytron_sdk.dll) is in the same directory as your executable in the final build

---

## Building and Testing Examples

All examples will only function properly in GameOS where the libraries and dlls are provided.

IMPORTANT: These examples will only work on GameOS Beta 1.1 version and up!
IMPORTANT 2: The wallet UI to approve/reject transactions might not be released with Beta 1.1 and come with a later version, thus making web3 examples not fully testable.

### Attestation

#### Linux

- `export IP_ADDRESS=DEVICE_IP`
    - `DEVICE_IP` above represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address
- `make examples-attestation-linux-x64`
- `scp -r ./build/linux-x64/bin/* playtron@$IP_ADDRESS:/home/playtron/cpp-linux`
- `ssh playtron@$IP_ADDRESS`
- `cd cpp-linux`
- `PACT_ATTESTATION_URL=https://pact.playtron.one LD_LIBRARY_PATH=.:/usr/lib64 ./attestation`
    - In a live app, the `PACT_ATTESTATION_URL` and `LD_LIBRARY_PATH` variables will be provided when executing the app.

#### Windows

- `export IP_ADDRESS=DEVICE_IP`
    - `DEVICE_IP` above represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address
- `make examples-attestation-win-x64`
- `scp -r ./build/win-x64/bin/* playtron@$IP_ADDRESS:/home/playtron/cpp-win`
- `ssh playtron@$IP_ADDRESS`
- `cd cpp-win`
- Export variables
```bash
export WINE_PREFIX=$(pwd)/wine_prefix
export STEAM_COMPAT_DATA_PATH=$WINE_PREFIX
export STEAM_COMPAT_PATH=~/.local/share/Steam && export STEAM_COMPAT_CLIENT_INSTALL_PATH=~/.local/share/Steam
```
- Create prefix folder
```bash
mkdir -p $WINE_PREFIX
ls ~/.local/share/playtron/tools/proton
# Look at the output of this command and take note of the installed proton versions, as it will be used in the next step
# Let's assume we have `proton-ge-9-27` installed for the next steps
```
- Initialize prefix
```bash
~/.local/share/playtron/tools/proton/proton-ge-9-27/proton run cmd.exe /c exit
# This initializes the windows wine prefix directory in which the example will execute
cp /usr/share/playtron/playtron.dll $WINE_PREFIX/pfx/drive_c/windows/system32/
# This is copying the playtron.dll to your wine prefix.
# This will already be done for you when executing the app via GameOS.
cp /usr/share/playtron/pact.dll $WINE_PREFIX/pfx/drive_c/windows/system32/
# This is copying the pact.dll to your wine prefix.
# This will already be done for you when executing the app via GameOS.
```
- `PACT_ATTESTATION_URL=https://pact.playtron.one LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ./attestation.exe`
    - In a live app, the `PACT_ATTESTATION_URL` and `LD_LIBRARY_PATH` variables will be provided when executing the app.

### Web3

#### Linux

- `export IP_ADDRESS=DEVICE_IP`
    - `DEVICE_IP` above represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address
- `make examples-web3-linux-x64`
- `scp -r ./build/linux-x64/bin/* playtron@$IP_ADDRESS:/home/playtron/cpp-linux`
- `ssh playtron@$IP_ADDRESS`
- `cd cpp-linux`
- `LD_LIBRARY_PATH=.:/usr/lib64 ./web3`
    - In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app.

#### Windows

- `export IP_ADDRESS=DEVICE_IP`
    - `DEVICE_IP` above represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address
- `make examples-web3-win-x64`
- `scp -r ./build/win-x64/bin/* playtron@$IP_ADDRESS:/home/playtron/cpp-win`
- `ssh playtron@$IP_ADDRESS`
- `cd cpp-win`
- Export variables
```bash
export WINE_PREFIX=$(pwd)/wine_prefix
export STEAM_COMPAT_DATA_PATH=$WINE_PREFIX
export STEAM_COMPAT_PATH=~/.local/share/Steam && export STEAM_COMPAT_CLIENT_INSTALL_PATH=~/.local/share/Steam
```
- Create prefix folder
```bash
mkdir -p $WINE_PREFIX
ls ~/.local/share/playtron/tools/proton
# Look at the output of this command and take note of the installed proton versions, as it will be used in the next step
# Let's assume we have `proton-ge-9-27` installed for the next steps
```
- Initialize prefix
```bash
~/.local/share/playtron/tools/proton/proton-ge-9-27/proton run cmd.exe /c exit
# This initializes the windows wine prefix directory in which the example will execute
cp /usr/share/playtron/playtron.dll $WINE_PREFIX/pfx/drive_c/windows/system32/
# This is copying the playtron.dll to your wine prefix.
# This will already be done for you when executing the app via GameOS.
cp /usr/share/playtron/pact.dll $WINE_PREFIX/pfx/drive_c/windows/system32/
# This is copying the pact.dll to your wine prefix.
# This will already be done for you when executing the app via GameOS.
```
- `LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ./web3.exe`
    - In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app.

---

## 🧩 API Reference

The Playtron C++ SDK provides convenient access to core GameOS platform services such as OS checks, remote attestation, and blockchain signing via Web3.

---

### 🔍 `playtron::sdk::os`

#### `bool is_playtron()`

Checks if the application is currently running on a Playtron GameOS device.

```cpp
#include <playtron/sdk/os.hxx>

if (playtron::sdk::os::is_playtron()) {
    // Running on GameOS
}
```

---

### `playtron::sdk::pact`

#### Class: `AttestationClient`

Used to initiate a TPM-based attestation session with the Playtron PACT service.

##### Constructor

```cpp
playtron::sdk::pact::AttestationClient client;
```

##### `SessionInfo create_session()`

Creates and returns a new attestation session. Call this once to initialize the session and receive a unique nonce and session ID.

```cpp
playtron::sdk::pact::SessionInfo info = client.create_session();
std::cout << "Nonce: " << info.nonce << ", Session ID: " << info.sessionId << std::endl;
```

##### `std::string get_quote(const std::string& nonce)`

Retrieves a TPM quote using the nonce from `create_session()`. This quote must be sent to the Playtron PACT server for validation.

```cpp
std::string quote = client.get_quote(info.nonce);
// send quote to server
```

##### Exception: `AttestationException`

Thrown if the attestation process fails at any stage.

---

### `playtron::sdk::web3`

Provides Web3 functionality integrated with the user's Playtron wallet.

#### `std::string get_wallet_address()`

Returns the Sui wallet address for the currently logged-in user.

```cpp
std::string address = playtron::sdk::web3::get_wallet_address();
std::cout << "User wallet address: " << address << std::endl;
```

---

#### `MessageResult sign_message(const std::string& providerAppId, const std::string& msg)`

Requests the user to sign an arbitrary message through the Playtron wallet UI.

```cpp
playtron::sdk::web3::MessageResult result =
    playtron::sdk::web3::sign_message("123", "Hello from my game!");

if (result.cancelled) {
    std::cerr << "User cancelled signing." << std::endl;
} else if (!result.error.empty()) {
    std::cerr << "Error signing: " << result.error << std::endl;
} else {
    std::cout << "Signed message: " << result.signature << std::endl;
}
```

---

#### `TransactionResult sign_and_execute_transaction(const std::string& providerAppId, const std::string& txBytes)`

Requests the user to sign and submit a Sui transaction. The transaction must be passed as a base64-encoded BCS payload.

```cpp
playtron::sdk::web3::TransactionResult tx =
    playtron::sdk::web3::sign_and_execute_transaction("123", base64_tx);

if (tx.cancelled) {
    std::cerr << "User cancelled transaction." << std::endl;
} else if (!tx.error.empty()) {
    std::cerr << "Transaction error: " << tx.error << std::endl;
} else {
    std::cout << "Transaction completed at: " << tx.completed_at << std::endl;
    std::cout << "Transaction result: " << tx.result << std::endl;
}
```

---

### ⚠# Exceptions

- **`UninitializedException`**: Thrown when the SDK is used without proper initialization, or outside a Playtron environment.
- **`AttestationException`**: Thrown during failures in the attestation flow.
---
