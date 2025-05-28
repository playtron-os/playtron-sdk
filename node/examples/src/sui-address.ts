import { Sui } from '@playtron/sdk';
import { exit } from 'process';

async function main() {
    console.log(`Running sui-address example...`)

    try {
        const address = await new Sui().getWalletAddress()

        console.log(`User sui wallet address is: ${address}`)
    } catch (err) {
        console.error(`Error during wallet address retrieval, err:${err}`)
        exit(1)
    }
}

main()
