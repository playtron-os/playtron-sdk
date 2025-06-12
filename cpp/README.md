# Playtron GameOS C++ SDK

Welcome to the official **Playtron GameOS C++ SDK** — a native C++ interface for building applications that integrate with the Playtron runtime.

This SDK supports both **Linux** and **Windows (via Wine/Proton)** and includes full examples for PACT attestation, sui signing, and more.

## Table of Contents

1. [Playtron GameOS C++ SDK](#playtron-gameos-c-sdk)
2. [Features](#features)
3. [Requirements](#requirements)
   - [Linux](#linux)
   - [Windows (Cross-compilation from Linux)](#windows-cross-compilation-from-linux)
4. [SDK Installation](#sdk-installation)
   - [Linux](#linux-1)
   - [Windows](#windows)
   - [Unreal Engine](#unreal-engine-integration)
5. [Building and Testing Examples](#building-and-testing-examples)
   - [Common Steps](#common-steps)
   - [Run Commands](#run-commands)
6. [🧩 API Reference](#🧩-api-reference)
   - [`playtron::sdk::os`](#playtronsdkos)
   - [`playtron::sdk::pact`](#playtronsdkpact)
     - [`AttestationClient`](#class-attestationclient)
   - [`playtron::sdk::sui`](#playtronsdksui)
   - [`playtron::sdk::manager`](#playtronsdkmanager)
7. [⚠ Exceptions](#⚠-exceptions)


---

## Features

- Remote PACT attestation via TPM
- Message signing and transaction execution
- Virtual Keyboard/Browser utilities
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

Include the SDK library in your build process:

### Linux

- Include the [libplaytron_sdk.so](./files/linux-x64/bin/libplaytron_sdk.so) file in your compilation
- If compiling manually, then add this to your command `-Ldirectory/to/sdk/file -lplaytron_sdk`

### Windows

- Include the [playtron_sdk.dll.a](./files/win-x64/lib/playtron_sdk.dll.a) lib file in your compilation
- If compiling manually, then add this to your command `-Ldirectory/to/sdk/file -l:playtron_sdk.dll.a`
- Ensure [playtron_sdk.dll](./files/win-x64/bin/playtron_sdk.dll) is in the same directory as your executable in the final build

### Unreal Engine Integration

To use the Playtron C++ SDK in a **Unreal Engine 5** project (Windows), follow these steps:

#### File Links

[playtron_sdk.dll](./files/win-x64/bin/playtron_sdk.dll)
[playtron_sdk.lib](./files/win-x64/lib/playtron_sdk.lib)
[libcurl.dll](./vendor/curl/bin-win-x64/libcurl.dll)
[libcurl.lib](./vendor/curl/lib-win-x64/libcurl.lib)
[zlib1.dll](./vendor/curl/bin-win-x64/zlib1.dll)

#### 1. Add SDK to Your Project

Place the SDK inside your project's `ThirdParty/PlaytronSDK` folder:

```
<YourProject>/ThirdParty/PlaytronSDK/
├── include/
│   └── playtron/...
├── lib/
│   ├── playtron_sdk.dll
│   ├── playtron_sdk.lib
│   ├── libcurl.dll
│   ├── libcurl.lib
│   └── zlib1.dll
```

#### 2. Update `YourModule.Build.cs`

Modify your module’s `.Build.cs` file to link against the SDK and bundle the required runtime dependencies:
Note that for the Editor to launch successfully, you might have to copy the .dll files to system32 windows folder or the engine binary folder

```csharp
string SDKPath = Path.Combine(ModuleDirectory, "../../ThirdParty/PlaytronSDK");

PublicIncludePaths.Add(Path.Combine(SDKPath, "include"));

PublicAdditionalLibraries.Add(Path.Combine(SDKPath, "lib", "playtron_sdk.lib"));
PublicAdditionalLibraries.Add(Path.Combine(SDKPath, "lib", "libcurl.lib"));

// Bundle required DLLs with packaged project
RuntimeDependencies.Add(
    Path.Combine("$(BinaryOutputDir)", "playtron_sdk.dll"),
    Path.Combine(SDKPath, "lib", "playtron_sdk.dll")
);

RuntimeDependencies.Add(
    Path.Combine("$(BinaryOutputDir)", "libcurl.dll"),
    Path.Combine(SDKPath, "lib", "libcurl.dll")
);

RuntimeDependencies.Add(
    Path.Combine("$(BinaryOutputDir)", "zlib1.dll"),
    Path.Combine(SDKPath, "lib", "zlib1.dll")
);
```

### 3. Packaging Notes

Ensure your packaging settings copy all `.dll` files correctly into the final build. If you get errors like *“DLL not found”* or *“Access violation”*, verify:

- DLLs are present in `Binaries/Win64`
- No processes (e.g., Unreal Editor) are locking the DLLs during packaging

You can use [Process Explorer](https://learn.microsoft.com/en-us/sysinternals/downloads/process-explorer) to check if any process is using the DLL.

---


## Building and Testing Examples

> 🛠️ Requires GameOS Beta 1.1+. Wallet UI for Sui may not be released in Beta 1.1.

### Common Steps

#### 1. Export IP Address

```bash
export IP_ADDRESS=DEVICE_IP  # Find in Settings → Internet → Wi-Fi → IP Address
```

#### 2. Build and Transfer Files

Replace `<example>` and `<platform>` with your desired target:

Examples available: `attestation` | `manager` | `sui`
Platforms available: `linux-x64` | `win-x64`

```bash
make examples-<example>-<platform>
scp -r ./build/<platform>/bin/* playtron@$IP_ADDRESS:/home/playtron/cpp-<platform>
ssh playtron@$IP_ADDRESS
cd cpp-<platform>
```

#### 3. Environment Setup for Windows (only)

```bash
export WINE_PREFIX=$(pwd)/wine_prefix
export STEAM_COMPAT_DATA_PATH=$WINE_PREFIX
export STEAM_COMPAT_PATH=~/.local/share/Steam
export STEAM_COMPAT_CLIENT_INSTALL_PATH=~/.local/share/Steam

mkdir -p $WINE_PREFIX
ls ~/.local/share/playtron/tools/proton  # Check installed versions

# Replace with your installed version:
~/.local/share/playtron/tools/proton/proton-ge-9-27/proton run cmd.exe /c exit

# Copy required DLLs:
cp /usr/lib64/libplaytron.so $WINE_PREFIX/pfx/drive_c/windows/system32/
cp /usr/share/playtron/playtron.dll $WINE_PREFIX/pfx/drive_c/windows/system32/
```

### Run Commands

(For Windows, see [Environment Setup for Windows](#3-environment-setup-for-windows-only))

| Example     | Platform | Run Command                                                                                     |
|-------------|----------|--------------------------------------------------------------------------------------------------|
| Attestation | Linux    | `PACT_ATTESTATION_URL=https://pact.playtron.one LD_LIBRARY_PATH=.:/usr/lib64 ./attestation`     |
| Attestation | Windows  | `PACT_ATTESTATION_URL=https://pact.playtron.one LD_LIBRARY_PATH=.:/usr/lib64 proton runinprefix ./attestation.exe` |
| Sui         | Linux    | `LD_LIBRARY_PATH=.:/usr/lib64 ./sui`                                                             |
| Sui         | Windows  | `LD_LIBRARY_PATH=.:/usr/lib64 proton runinprefix ./sui.exe`                                      |
| Manager     | Linux    | `LD_LIBRARY_PATH=.:/usr/lib64 ./manager`                                                         |
| Manager     | Windows  | `LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ./manager.exe`                                  |

---

## 🧩 API Reference

The Playtron C++ SDK provides convenient access to core GameOS platform services such as OS checks, remote attestation, and blockchain signing via Sui.

---

### `playtron::sdk::os`

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

### `playtron::sdk::sui`

Provides Sui functionality integrated with the user's Playtron wallet.

#### `std::string get_wallet_address()`

Returns the Sui wallet address for the currently logged-in user.

```cpp
std::string address = playtron::sdk::sui::get_wallet_address();
std::cout << "User wallet address: " << address << std::endl;
```

---

#### `SignResult sign_message(const std::string& providerAppId, const std::string& msg)`

Requests the user to sign an arbitrary message through the Playtron wallet UI.

```cpp
playtron::sdk::sui::SignResult result =
    playtron::sdk::sui::sign_message("123", "Hello from my game!");

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
playtron::sdk::sui::TransactionResult tx =
    playtron::sdk::sui::sign_and_execute_transaction("123", base64_tx);

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

#### `SignResult sign_transaction(const std::string& providerAppId, const std::string& txBytes)`

Requests the user to sign a transaction to be executed in-game.

```cpp
playtron::sdk::sui::SignResult result =
    playtron::sdk::sui::sign_transaction("123", base64_tx);

if (result.cancelled) {
    std::cerr << "User cancelled signing." << std::endl;
} else if (!result.error.empty()) {
    std::cerr << "Error signing: " << result.error << std::endl;
} else {
    std::cout << "Signed tx: " << result.signature << std::endl;
}
```

---

### `playtron::sdk::manager`

#### `void show_keyboard()`

Requests to show the in-game virtual keyboard in GameOS.

```cpp
#include <playtron/sdk/manager.hxx>

playtron::sdk::manager::show_keyboard();
```

---

#### `void hide_keyboard()`

Requests to hide the in-game virtual keyboard in GameOS.

```cpp
#include <playtron/sdk/manager.hxx>

playtron::sdk::manager::hide_keyboard();
```

---

#### `void open_browser(const std::string& url)`

Requests to open the browser and navigate to a specified URL in GameOS.

```cpp
#include <playtron/sdk/manager.hxx>

playtron::sdk::manager::open_browser("https://google.com");
```

---

#### `void close_browser()`

Requests to close the browser in GameOS.

```cpp
#include <playtron/sdk/manager.hxx>

playtron::sdk::manager::close_browser();
```

---

### ⚠ Exceptions

- **`UninitializedException`**: Thrown when the SDK is used without proper initialization, or outside a Playtron environment.
- **`AttestationException`**: Thrown during failures in the attestation flow.
---
