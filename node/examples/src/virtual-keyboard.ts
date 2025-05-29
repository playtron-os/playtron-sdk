import { Manager } from '@playtron/sdk';
import { sleep } from './utils';

async function main() {
    console.log(`Running virtual-keyboard example...`)

    const manager = new Manager()

    console.log(`Showing virtual keyboard...`)
    await manager.showKeyboard()

    console.log(`Waiting 5 seconds...`)
    await sleep(5000)

    console.log(`Hiding virtual keyboard...`)
    await manager.hideKeyboard()
}

main()
