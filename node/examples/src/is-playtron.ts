import { OS } from '@playtron/sdk';

async function main() {
    console.log(`Running is-playtron example...`)

    const isPlaytron = await new OS().isPlaytron();

    if (isPlaytron) {
        console.log(`Running in playtron`)
    } else {
        console.log(`Not running in playtron`)
    }
}

main()
