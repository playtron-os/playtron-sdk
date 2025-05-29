import { Manager } from '@playtron/sdk';
import { sleep } from './utils';

const URL = 'https://google.com'

async function main() {
    console.log(`Running browser example...`)

    const manager = new Manager()

    console.log(`Opening browser url: ${URL}...`)
    await manager.openBrowser(URL)

    console.log(`Waiting 5 seconds...`)
    await sleep(5000)

    console.log(`Closing browser...`)
    await manager.closeBrowser()
}

main()
