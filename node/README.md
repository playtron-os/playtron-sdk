# Playtron GameOS Node.js SDK

Welcome to the official **Playtron GameOS Node.js SDK** — a JavaScript/TypeScript interface for integrating applications with the Playtron runtime. It provides access to platform-level features like remote PACT attestation and Sui wallet functions, via native bindings.

This SDK is designed for **Node.js apps running on GameOS** and includes TypeScript-compatible classes with async methods.

## Table of Contents

1. [Playtron GameOS Node.js SDK](#playtron-gameos-nodejs-sdk)
2. [📦 Features](#📦-features)
3. [💻 Requirements](#💻-requirements)
4. [🚀 Installation](#🚀-installation)
5. [🧪 Building and Testing Examples](#🧪-building-and-testing-examples)  
   - [🔧 Download NodeJS](#🔧-download-nodejs)  
     - [Linux](#linux)  
     - [Windows](#windows)  
   - [🔧 Common Setup](#🔧-common-setup)  
   - [🪟 Windows Proton Environment Setup](#🪟-windows-proton-environment-setup)  
   - [🧪 Running Examples](#🧪-running-examples)  
     - [Run (Linux)](#run-linux)  
     - [Run (Windows)](#run-windows)
6. [📚 API Reference](#📚-api-reference)  
   - [`class OS`](#class-os)  
   - [`class AttestationClient`](#class-attestationclient)  
   - [`class Sui`](#class-sui)  
   - [`class Manager`](#class-manager)
7. [🧾 Types](#🧾-types)

---

## 📦 Features

- TPM-based remote attestation
- Sui wallet integration for signing and executing transactions
- Virtual Keyboard/Browser utilities
- Detect if running on GameOS
- Native bindings via ffi-rs
- TypeScript support

---

## 💻 Requirements

- Node.js 18+
- GameOS Beta 1.1+ (provides required native libraries)

---

## 🚀 Installation

```bash
npm install @playtron/sdk
```

---

## 🧪 Building and Testing Examples

> 🛠️ Requires GameOS Beta 1.1+. Some Sui wallet functions may not be available until later releases.

### 🔧 Download NodeJS

#### Linux

- Download the linux node standalone binary from here: https://nodejs.org/dist/v22.16.0/node-v22.16.0-linux-x64.tar.xz
- Unzip into ~/Downloads directory

#### Windows

- Download the windows node zip from here: https://nodejs.org/dist/v22.16.0/node-v22.16.0-win-x64.zip
- Unzip into ~/Downloads directory

### 🔧 Common Setup

Replace `<example>` and `<platform>` with your desired target:

Examples available: `attestation` | `browser` | `is-playtron` | `sui-address` | `sui-sign-and-execute-transaction` | `sui-sign-message` | `sui-sign-transaction` | `virtual-keyboard`
Platforms available: `linux-x64` | `win-x64`

```bash
export IP_ADDRESS=DEVICE_IP  # Find in Settings → Internet → Wi-Fi → IP Address
cd ./examples
pnpm install
BUILD_FILE=<example> pnpm build
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-<platform>
scp -r ~/Downloads/node-v22.16.0-<platform>/* playtron@$IP_ADDRESS:/home/playtron/node-v22-<platform>
ssh playtron@$IP_ADDRESS
cd node-<platform>
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

### 🧪 Running Examples

#### Run (Linux)
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/node-v22-linux-x64/bin/node ./index
```

#### Run (Windows)
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ~/node-v22-win-x64/node.exe ./index
```

---

## 📚 API Reference

### `class OS`

- `isPlaytron(): Promise<boolean>`
  Returns `true` if running on GameOS, otherwise `false`.

---

### `class AttestationClient`

- `init(): Promise<void>`  
  Loads and initializes native TPM support.

- `createSession(): Promise<SessionInfo>`  
  Begins a new attestation session. Returns a nonce and session ID.

- `getQuote(nonce: string): Promise<string>`  
  Generates a TPM quote based on the provided nonce.

#### Exceptions

- `AttestationException`: Thrown on attestation errors.

---

### `class Sui`

- `getWalletAddress(): Promise<string>`  
  Returns the wallet address from the user’s Playtron wallet.

- `signMessage(providerAppId: string, message: string): Promise<SignResult>`  
  Signs a message via the wallet UI.

- `signAndExecuteTransaction(providerAppId: string, txBytes: string): Promise<TransactionResult>`  
  Signs and submits a Sui transaction.

- `signTransaction(providerAppId: string, txBytes: string): Promise<SignResult>`  
  Signs a Sui transaction for in-game execution.

---

### `class Manager`

- `showKeyboard(): Promise<void>`
  Requests the OS to show the virtual in game keyboard.

- `isKeyboardOpen(): Promise<bool>`
  Checks whether the in-game keyboard is open.

- `hideKeyboard(): Promise<void>`
  Requests the OS to hide the virtual in game keyboard.

- `openBrowser(url: string): Promise<void>`
  Requests the OS to open browser to a URL.

- `closeBrowser(): Promise<void>`
  Requests the OS to close the browser.

---

## 🧾 Types

```ts
type SignResult = {
  error: string;
  cancelled: boolean;
  signature: string;
}

type TransactionResult = {
  error: string;
  cancelled: boolean;
  completedAt: number;
  result: string;
}

type SessionInfo = {
  nonce: string;
  sessionId: string;
}
```
