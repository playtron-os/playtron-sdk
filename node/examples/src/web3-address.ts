import { Web3 } from '@playtron/sdk';
import { exit } from 'process';

async function main() {
    console.log(`Running web3-address example...`)

    try {
        const address = await new Web3().getWalletAddress()

        console.log(`User sui wallet address is: ${address}`)
    } catch (err) {
        console.error(`Error during wallet address retrieval, err:${err}`)
        exit(1)
    }
}

main()
