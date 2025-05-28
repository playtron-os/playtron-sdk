import { getFullnodeUrl, SuiClient } from '@mysten/sui/client';
import { Transaction } from '@mysten/sui/transactions';
import { Sui } from '@playtron/sdk';
import { exit } from 'process';

// Note: This can be any address. It is used to send a coin object
const SENDER = "0x8b338e67d9f168526b26ba9e444c439b45e7c6f7766e706adeab81b22c58622d";
// Note: This can be any address. It is used to receive a coin object
const RECEIVER = "0xb862ab02807a85466d98bc677d84ffceb58c7864fd3b29f885d049f1f7c30c44";
const TRANSFER_AMOUNT = 100_000_000; // 0.1 SUI

async function main() {
    console.log(`Running sui-sign-transaction example...`)

    try {
        const txBytes = await simpleCoinTransferTxn(SENDER, RECEIVER, TRANSFER_AMOUNT)
        console.log(`Sending and waiting for user response`)

        // provider app id is required in production, for testing in testnet it can be empty
        const res = await new Sui().signTransaction('', txBytes)

        if (res.cancelled) {
            console.log(`User cancelled signing`)
        } else if (res.error) {
            console.log(`Error during signing, err:${res.error}`)
        } else {
            console.log(`Signature: ${res.signature}`)
        }
    } catch (err) {
        console.error(`Error during transaction signing, err:${err}`)
        exit(1)
    }
}

async function simpleCoinTransferTxn(sender: string, receiver: string, amount: number) {
    const tx = new Transaction()
    tx.setSender(sender)

    const suiCoin = tx.splitCoins(tx.gas, [amount])
    tx.transferObjects(
        [suiCoin],
        receiver,
    )

    const suiClient = new SuiClient({ url: getFullnodeUrl('testnet') });
    const txBytes = await tx.build({
        client: suiClient
    })

    return Buffer.from(txBytes).toString('base64')
}

main()
