# Playtron GameOS C# SDK

Welcome to the official **Playtron GameOS C# SDK** — a .NET interface for building applications that integrate with the Playtron runtime.

This SDK supports both **Linux** and **Windows (via Wine/Proton)** and includes full examples for attestation, web3 signing, and more.

---

## Features

- Remote attestation via TPM
- Message signing and transaction execution
- Cross-platform support (Linux + Wine/Proton on Windows)
- Clean, minimal examples in C#

---

## Requirements

- GameOS Beta 1.1+ (provides required native libraries)

### Linux
- .NET 8+ SDK
- Wine (for Proton testing)

### Windows
- .NET 8+ SDK
- Visual Studio 2022 or newer

---

## Installation

To use the SDK, follow these steps:

### Linux

- Install Playtron.SDK in your project
```bash
dotnet add package Playtron.SDK
```

### Windows

- Install Playtron.SDK in your project
```bash
dotnet add package Playtron.SDK
```

---

## Building and Running

All examples will only function properly in GameOS where the libraries and dlls are provided.

IMPORTANT: These examples will only work on GameOS Beta 1.1 version and up!
IMPORTANT 2: The wallet UI to approve/reject transactions might not be released with Beta 1.1 and come with a later version, thus making web3 examples not fully testable.

### Attestation

#### Linux

- `export IP_ADDRESS=DEVICE_IP`
    - `DEVICE_IP` above represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address
- Build Example
```bash
cd Examples/Attestation
dotnet build \
    --runtime linux-x64 \
    -c Release \
    --self-contained true
```
- `scp -r ./bin/Release/net8.0/linux-x64/* playtron@$IP_ADDRESS:/home/playtron/csharp-linux`
- `ssh playtron@$IP_ADDRESS`
- `cd csharp-linux`
- `PACT_ATTESTATION_URL=https://pact.playtron.one LD_LIBRARY_PATH=.:/usr/lib64 ./Attestation`
    - In a live app, the `PACT_ATTESTATION_URL` and `LD_LIBRARY_PATH` variables will be provided when executing the app.

#### Windows

- `export IP_ADDRESS=DEVICE_IP`
    - `DEVICE_IP` above represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address
- Build Example
```bash
cd Examples/Attestation
dotnet build \
    --runtime win-x64 \
    -c Release \
    --self-contained true
```
- `scp -r ./bin/Release/net8.0/win-x64/* playtron@$IP_ADDRESS:/home/playtron/csharp-win`
- `ssh playtron@$IP_ADDRESS`
- `cd csharp-win`
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
- `PACT_ATTESTATION_URL=https://pact.playtron.one LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ./Attestation.exe`
    - In a live app, the `PACT_ATTESTATION_URL` and `LD_LIBRARY_PATH` variables will be provided when executing the app.

### Web3

#### Linux

- `export IP_ADDRESS=DEVICE_IP`
    - `DEVICE_IP` above represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address
- Build Example
```bash
cd Examples/Web3
dotnet build \
    --runtime linux-x64 \
    -c Release \
    --self-contained true
```
- `scp -r ./bin/Release/net8.0/linux-x64/* playtron@$IP_ADDRESS:/home/playtron/csharp-linux`
- `ssh playtron@$IP_ADDRESS`
- `cd csharp-linux`
- `LD_LIBRARY_PATH=.:/usr/lib64 ./Web3`
    - In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app.

#### Windows

- `export IP_ADDRESS=DEVICE_IP`
    - `DEVICE_IP` above represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address
- Build Example
```bash
cd Examples/Web3
dotnet build \
    --runtime win-x64 \
    -c Release \
    --self-contained true
```
- `scp -r ./bin/Release/net8.0/win-x64/* playtron@$IP_ADDRESS:/home/playtron/csharp-win`
- `ssh playtron@$IP_ADDRESS`
- `cd csharp-win`
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
- `LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ./Web3.exe`
    - In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app.

---

## 🧩 API Reference (C#)

The Playtron SDK provides convenient access to GameOS platform features including environment detection, TPM-based remote attestation, and wallet-based Web3 interactions.

---

### 🔍 `Playtron.SDK.OS`

#### `bool OS.IsPlaytron()`

Determines whether the application is currently running on a Playtron-enabled environment.

```csharp
if (OS.IsPlaytron())
{
    Console.WriteLine("Running on Playtron GameOS.");
}
```

---

### 🔐 `Playtron.SDK.PACT.AttestationClient`

Used to initiate remote attestation with the Playtron PACT service via the local TPM.

#### Constructor

```csharp
var client = new AttestationClient();
```

Throws `AttestationException` if the TPM library fails to initialize.

#### `Task<SessionInfo> CreateSession()`

Initializes a new attestation session and returns a nonce and session ID.

```csharp
SessionInfo session = await client.CreateSession();
Console.WriteLine($"Nonce: {Convert.ToBase64String(session.Nonce)}, SessionId: {session.SessionId}");
```

#### `string GetQuote(byte[] nonce)`

Generates a TPM quote for the provided nonce.

```csharp
string quote = client.GetQuote(session.Nonce);
// Send quote to attestation server
```

#### Exception: `AttestationException`

Thrown when initialization, session setup, or quote generation fails.

---

### 🌐 `Playtron.SDK.Web3`

Interfaces with the user’s Playtron wallet for Web3-related functionality.

#### `string Web3.GetWalletAddress()`

Returns the user’s current Sui wallet address.

```csharp
string address = Web3.GetWalletAddress();
Console.WriteLine($"Wallet address: {address}");
```

#### `MessageResult Web3.SignMessage(string providerAppId, string message)`

Requests the user to sign a message through their wallet UI.

```csharp
var result = Web3.SignMessage("123", "Hello!");

if (result.Cancelled)
    Console.WriteLine("User cancelled.");
else if (!string.IsNullOrEmpty(result.Error))
    Console.WriteLine($"Error: {result.Error}");
else
    Console.WriteLine($"Signature: {result.Signature}");
```

#### `TransactionResult Web3.SignAndExecuteTransaction(string providerAppId, string txBytes)`

Signs and submits a base64-encoded Sui transaction via the Playtron wallet.

```csharp
var txResult = Web3.SignAndExecuteTransaction("123", base64Tx);

if (txResult.Cancelled)
    Console.WriteLine("Transaction cancelled.");
else if (!string.IsNullOrEmpty(txResult.Error))
    Console.WriteLine($"Error: {txResult.Error}");
else
    Console.WriteLine($"Completed at: {txResult.CompletedAt}, Result: {txResult.Result}");
```

---

### ⚠# Exceptions

- **`AttestationException`** — Thrown when TPM attestation fails during session setup or quote generation.
- **`InvalidOperationException` / `ArgumentException`** — Thrown when input validation fails or signing functions return null or deserialization fails.
