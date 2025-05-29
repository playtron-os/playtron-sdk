# Playtron SDKs

This repository contains multiple SDKs for interfacing with **Playtron GameOS** across different languages.

Each SDK provides access to platform-level features such as environment detection, remote PACT attestation, and Sui wallet integration.

---

## Requirements

- GameOS Beta 1.1+ (provides required native libraries)

---

## Testnet

If running the SDK for testing purposes and the goal is to target Sui `testnet` network, then you can change the network in GameOS like this:
```bash
ssh playtron@DEVICE_IP # Find in Settings → Internet → Wi-Fi → IP Address
echo "PLAYTRON_ENOKI_NETWORK=testnet" > ~/.config/environment.d/PLAYTRON_ENOKI_NETWORK.conf
systemctl --user restart playserve
```

If needed to go back to mainnet, simply replace `testnet` above for `mainnet` and re-run that command.

---

## Provider App Id Requirements

In the Sui APIs, it is required to provider a `providerAppId`. This is the id associated to your game in the respective provider's store (ex: steam | epic | gog).

If running in `testnet`, it is possible to use an empty `providerAppId` string for quick iteration or if running the examples in this repo.

---

## SDKs

### 🔷 Node.js SDK

Location: [`/node/README.md`](./node/README.md)

- JavaScript/TypeScript support
- Uses `ffi-rs` for native bindings
- Works with `libplaytron` and `libpact` on GameOS

---

### 🟦 C# SDK

Location: [`/csharp/README.md`](./csharp/README.md)

- .NET 8.0+ compatible
- Works with `libplaytron` and `libpact` on GameOS

---

### 🟪 C++ SDK

Location: [`/cpp/README.md`](./cpp/README.md)

- Native C++ bindings to Playtron libraries
- Includes lower-level access and build tooling
- Works with `libplaytron` and `libpact` on GameOS

---
