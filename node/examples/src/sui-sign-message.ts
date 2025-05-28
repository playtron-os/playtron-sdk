import { Sui } from '@playtron/sdk';
import { exit } from 'process';

async function main() {
    console.log(`Running sui-sign-message example...`)

    const msg = 'My message to sign'
    console.log(`Signing message: "${msg}"`)

    try {
        console.log(`Sending and waiting for user response`)

        // provider app id is required in production, for testing in testnet it can be empty
        const res = await new Sui().signMessage('', msg)

        if (res.cancelled) {
            console.log(`User cancelled signing`)
        } else if (res.error) {
            console.log(`Error during signing, err:${res.error}`)
        } else {
            console.log(`Signature: ${res.signature}`)
        }
    } catch (err) {
        console.error(`Error during message signing, err:${err}`)
        exit(1)
    }
}

main()
