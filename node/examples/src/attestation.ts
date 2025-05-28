import axios from 'axios';
import { OS, AttestationClient } from '@playtron/sdk';
import { exit } from 'process';

async function main() {
    console.log(`Running attestation example...`)

    try {
        console.log(`Checking if on a Playtron device...`)
        const isPlaytron = await new OS().isPlaytron();

        if (isPlaytron) {
            console.log(`Running in playtron`)
        } else {
            console.log(`Not running in playtron`)
            return;
        }

        console.log(`Creating attestation client...`)
        const client = new AttestationClient()

        console.log(`Creating attestation session...`)
        const sessionInfo = await client.createSession()
        console.log(`Session ID: ${sessionInfo.sessionId}`)
        console.log(`Nonce: ${Buffer.from(sessionInfo.nonce).toString('base64')}`)

        console.log(`Getting quote from TPM...`)
        const quote = await client.getQuote(sessionInfo.nonce)
        console.log(`Quote: ${quote}`)

        console.log(`Sending attestation request...`)
        const response = await axios.post(
            `${process.env.PACT_ATTESTATION_URL}/api/v1/session/attest`,
            quote,
            {
                headers: {
                    Accept: 'application/json',
                    'Content-Type': 'application/json',
                    'X-Session-Id': sessionInfo.sessionId,
                },
            },
        );

        if (response.status === 200) {
            console.log("Attestation successful:", response.data);
        } else {
            console.log(`Attestation request failed with status code: ${response.status}, data: ${response.data}`)
        }
    } catch (err) {
        console.error(`Error during attestation, err:${err}`)
        exit(1)
    }
}

main()
