# Playtron GameOS C# SDK

Welcome to the official **Playtron GameOS C# SDK** — a .NET interface for building applications that integrate with the Playtron runtime.

This SDK supports **Linux** and **Windows (via Wine/Proton)**, with full examples for PACT attestation, Sui signing, and more.

---

## 📦 Features

- Remote TPM-based attestation
- Sui message and transaction signing
- Virtual Keyboard/Browser utilities
- Cross-platform support: Linux and Windows (via Wine/Proton)
- Clean .NET 8+ examples

---

## 💻 Requirements

**GameOS Beta 1.1+** required.

### Linux
- .NET 8+ SDK
- Wine (for Proton compatibility testing)

### Windows
- .NET 8+ SDK
- Visual Studio 2022 or newer

---

## 🚀 Installation

```bash
# Linux & Windows (same command)
dotnet add package Playtron.SDK
```

---

## 🧪 Building and Running Examples

> 🛠️ Requires GameOS Beta 1.1+. Wallet UI for Sui may not be released in Beta 1.1.

### 🔧 Common Setup

Replace `<example>` and `<platform>` with your desired target:

Examples available: `Attestation` | `Manager` | `Sui`
Platforms available: `linux-x64` | `win-x64`

```bash
export IP_ADDRESS=DEVICE_IP
cd Examples/<example>
dotnet build --runtime <platform> -c Release --self-contained true
scp -r ./bin/Release/net8.0/<platform>/* playtron@$IP_ADDRESS:/home/playtron/csharp-<platform>
ssh playtron@$IP_ADDRESS
cd csharp-<platform>
```

### 🪟 Windows Proton Environment Setup

```bash
export WINE_PREFIX=$(pwd)/wine_prefix
export STEAM_COMPAT_DATA_PATH=$WINE_PREFIX
export STEAM_COMPAT_PATH=~/.local/share/Steam
export STEAM_COMPAT_CLIENT_INSTALL_PATH=~/.local/share/Steam

mkdir -p $WINE_PREFIX
~/.local/share/playtron/tools/proton/proton-ge-9-27/proton run cmd.exe /c exit
cp /usr/share/playtron/playtron.dll $WINE_PREFIX/pfx/drive_c/windows/system32/
cp /usr/share/playtron/pact.dll $WINE_PREFIX/pfx/drive_c/windows/system32/
```

### 🔐 Attestation Example

#### Linux
```bash
LD_LIBRARY_PATH=.:/usr/lib64 PACT_ATTESTATION_URL=https://pact.playtron.one ./Attestation
```

#### Windows
```bash
LD_LIBRARY_PATH=.:/usr/lib64   ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ./Attestation.exe
```

### 🌐 Sui Example

#### Linux
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ./Sui
```

#### Windows
```bash
LD_LIBRARY_PATH=.:/usr/lib64   ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ./Sui.exe
```

### 🧰 Manager Example

#### Linux
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ./Manager
```

#### Windows
```bash
LD_LIBRARY_PATH=.:/usr/lib64   ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ./Manager.exe
```

---

## 🧩 API Reference (C#)

### `Playtron.SDK.OS`

#### `bool OS.IsPlaytron()`
Returns true if running on a Playtron-enabled environment.

```csharp
if (OS.IsPlaytron())
    Console.WriteLine("Running on GameOS");
```

---

### `Playtron.SDK.PACT.AttestationClient`

#### `AttestationClient()` constructor
Throws `AttestationException` if TPM fails to initialize.

#### `Task<SessionInfo> CreateSession()`
Starts attestation session, returns nonce and session ID.

#### `string GetQuote(byte[] nonce)`
Returns TPM quote for server submission.

---

### `Playtron.SDK.Sui`

#### `string GetWalletAddress()`
Returns the user’s wallet address.

#### `SignResult SignMessage(string providerAppId, string message)`
Asks the user to sign a message.

#### `TransactionResult SignAndExecuteTransaction(string providerAppId, string txBytes)`
Signs and executes a base64-encoded transaction.

#### `SignResult SignTransaction(string providerAppId, string txBytes)`
Signs transaction for in-game use.

---

### `Playtron.SDK.Manager`

#### `void ShowKeyboard()`
Show in-game virtual keyboard.

#### `void HideKeyboard()`
Hide in-game virtual keyboard.

#### `void OpenBrowser(string url)`
Open browser to a URL.

#### `void CloseBrowser()`
Close the browser.

---

## ⚠ Exceptions

- `AttestationException` — attestation or TPM errors
- `InvalidOperationException` / `ArgumentException` — input validation or null return errors
