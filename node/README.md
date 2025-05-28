# Playtron GameOS Node.js SDK

Welcome to the official **Playtron GameOS Node.js SDK** — a JavaScript/TypeScript interface for integrating applications with the Playtron runtime. It provides access to platform-level features like remote PACT attestation and Sui wallet functions, via native bindings.

This SDK is designed for **Node.js apps running on GameOS** and includes TypeScript-compatible classes with async methods.

## Table of Contents

1. [Playtron GameOS Node.js SDK](#playtron-gameos-nodejs-sdk)
2. [Features](#features)
3. [Requirements](#requirements)
4. [Installation](#installation)
5. [Building and Testing Examples](#building-and-testing-examples)
    - [PACT Attestation](#attestation)
        - [Linux](#linux)
        - [Windows](#windows)
    - [Sui Address](#sui-address)
        - [Linux](#linux-1)
        - [Windows](#windows-1)
    - [Sui Sign Message](#sui-sign-message)
        - [Linux](#linux-2)
        - [Windows](#windows-2)
    - [Sui Sign and Execute Transaction](#sui-sign-and-execute-transaction)
        - [Linux](#linux-3)
        - [Windows](#windows-3)
6. [API Reference](#api-reference)
    - [class OS](#class-os)
    - [class AttestationClient](#class-attestationclient)
    - [class Sui](#class-sui)
7. [Types](#types)

---

## Features

- TPM-based remote attestation
- Sui wallet integration for signing and executing transactions
- Detect if running on GameOS
- Native bindings via ffi-rs
- TypeScript support

---

## Requirements

- Node.js 18+
- GameOS Beta 1.1+ (provides required native libraries)

---

## Installation

1. Install SDK:
```bash
npm install @playtron/sdk
```

---

## Building and Testing Examples

All examples will only function properly in GameOS where the libraries and dlls are provided.

IMPORTANT: These examples will only work on GameOS Beta 1.1 version and up!
IMPORTANT 2: The wallet UI to approve/reject transactions might not be released with Beta 1.1 and come with a later version, thus making sui examples not fully testable.

### Attestation

#### Linux

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=attestation pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-linux
```
- Download the linux node standalone binary from here: https://nodejs.org/en/download
- Copy the node binary to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-linux-x64/bin/node playtron@$IP_ADDRESS:/home/playtron/node
```
```bash
ssh playtron@$IP_ADDRESS
cd node-linux
```
- Run (In a live app, the `PACT_ATTESTATION_URL` and `LD_LIBRARY_PATH` variables will be provided when executing the app):
```bash
PACT_ATTESTATION_URL=https://pact.playtron.one LD_LIBRARY_PATH=.:/usr/lib64 ~/node ./index
```

#### Windows

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=attestation pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-win
```
- Download the windows node zip from here: https://nodejs.org/dist/v22.16.0/node-v22.16.0-win-x64.zip
- Copy the node zip to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-win-x64.zip playtron@$IP_ADDRESS:/home/playtron
```
- Ssh into the device and unzip node:
```bash
ssh playtron@$IP_ADDRESS
unzip node-v22.16.0-win-x64.zip
cd node-win
```
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
- Run (In a live app, the `PACT_ATTESTATION_URL` and `LD_LIBRARY_PATH` variables will be provided when executing the app):
```bash
PACT_ATTESTATION_URL=https://pact.playtron.one LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ~/node-v22.16.0-win-x64/node.exe ./index
```

### Sui Address

#### Linux

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=sui-address pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-linux
```
- Download the linux node standalone binary from here: https://nodejs.org/en/download
- Copy the node binary to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-linux-x64/bin/node playtron@$IP_ADDRESS:/home/playtron/node
```
```bash
ssh playtron@$IP_ADDRESS
cd node-linux
```
- Run (In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app.):
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/node ./index
```

#### Windows

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=sui-address pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-win
```
- Download the windows node zip from here: https://nodejs.org/dist/v22.16.0/node-v22.16.0-win-x64.zip
- Copy the node zip to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-win-x64.zip playtron@$IP_ADDRESS:/home/playtron
```
- Ssh into the device and unzip node:
```bash
ssh playtron@$IP_ADDRESS
unzip node-v22.16.0-win-x64.zip
cd node-win
```
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
- Run (In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app):
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ~/node-v22.16.0-win-x64/node.exe ./index
```

### Sui Sign Message

#### Linux

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=sui-sign-message pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-linux
```
- Download the linux node standalone binary from here: https://nodejs.org/en/download
- Copy the node binary to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-linux-x64/bin/node playtron@$IP_ADDRESS:/home/playtron/node
```
- Ssh into the device:
```bash
ssh playtron@$IP_ADDRESS
cd node-linux
```
- Run (In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app.):
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/node ./index
```

#### Windows

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=sui-sign-message pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-win
```
- Download the windows node zip from here: https://nodejs.org/dist/v22.16.0/node-v22.16.0-win-x64.zip
- Copy the node zip to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-win-x64.zip playtron@$IP_ADDRESS:/home/playtron
```
- Ssh into the device and unzip node:
```bash
ssh playtron@$IP_ADDRESS
unzip node-v22.16.0-win-x64.zip
cd node-win
```
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
- Run (In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app):
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ~/node-v22.16.0-win-x64/node.exe ./index
```

### Sui Sign Transaction

#### Linux

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=sui-sign-transaction pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-linux
```
- Download the linux node standalone binary from here: https://nodejs.org/en/download
- Copy the node binary to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-linux-x64/bin/node playtron@$IP_ADDRESS:/home/playtron/node
```
- Ssh into the device:
```bash
ssh playtron@$IP_ADDRESS
cd node-linux
```
- Run (In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app.):
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/node ./index
```

#### Windows

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=sui-sign-transaction pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-win
```
- Download the windows node zip from here: https://nodejs.org/dist/v22.16.0/node-v22.16.0-win-x64.zip
- Copy the node zip to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-win-x64.zip playtron@$IP_ADDRESS:/home/playtron
```
- Ssh into the device and unzip node:
```bash
ssh playtron@$IP_ADDRESS
unzip node-v22.16.0-win-x64.zip
cd node-win
```
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
- Run (In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app):
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ~/node-v22.16.0-win-x64/node.exe ./index
```

### Sui Sign and Execute Transaction

#### Linux

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=sui-sign-and-execute-transaction pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-linux
```
- Download the linux node standalone binary from here: https://nodejs.org/en/download
- Copy the node binary to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-linux-x64/bin/node playtron@$IP_ADDRESS:/home/playtron/node
```
```bash
ssh playtron@$IP_ADDRESS
cd node-linux
```
- Run (In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app.):
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/node ./index
```

#### Windows

- Export IP (`DEVICE_IP` below represents the local IP of your device, which can be found in Settings -> Internet -> {wifi connected} -> IP Address):
```bash
export IP_ADDRESS=DEVICE_IP
```
- Build the example:
```bash
cd ./examples
pnpm install
BUILD_FILE=sui-sign-and-execute-transaction pnpm build
```
- Copy built code to device:
```bash
scp -r ./dist/* playtron@$IP_ADDRESS:/home/playtron/node-win
```
- Download the windows node zip from here: https://nodejs.org/dist/v22.16.0/node-v22.16.0-win-x64.zip
- Copy the node zip to the target device:
```bash
scp -r ~/Downloads/node-v22.16.0-win-x64.zip playtron@$IP_ADDRESS:/home/playtron
```
- Ssh into the device and unzip node:
```bash
ssh playtron@$IP_ADDRESS
unzip node-v22.16.0-win-x64.zip
cd node-win
```
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
- Run (In a live app, the `LD_LIBRARY_PATH` variable will be provided when executing the app):
```bash
LD_LIBRARY_PATH=.:/usr/lib64 ~/.local/share/playtron/tools/proton/proton-ge-9-27/proton runinprefix ~/node-v22.16.0-win-x64/node.exe ./index
```

---

## API Reference

### `class OS`

- `isPlaytron(): Promise<boolean>`  
  Returns `true` if running on GameOS, otherwise `false`.

---

### `class AttestationClient`

- `init(): Promise<void>`  
  Loads and initializes native TPM support.

- `createSession(): Promise<SessionInfo>`  
  Begins a new attestation session. Returns a nonce and session ID.

- `getQuote(nonce: Uint8Array): Promise<string>`  
  Generates a TPM quote based on the provided nonce.

#### Exceptions

- `AttestationException`: Thrown on attestation errors.

---

### `class Sui`

- `getWalletAddress(): Promise<string>`  
  Returns the wallet address from the user’s Playtron wallet.

- `signMessage(providerAppId: string, message: string): Promise<MessageResult>`  
  Signs a message via the wallet UI.

- `signAndExecuteTransaction(providerAppId: string, txBytes: string): Promise<TransactionResult>`  
  Signs and submits a Sui transaction.

---

## Types

```ts
type MessageResult = {
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
  nonce: Uint8Array;
  sessionId: string;
}
```

---
