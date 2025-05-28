using Playtron.SDK;

Console.WriteLine("Fetching wallet address...");
string currentAddress = Web3.GetWalletAddress();
Console.WriteLine($"Current address: {currentAddress}");

while (true)
{
    Console.WriteLine("Choose an action:");
    Console.WriteLine("  1) Sign a message");
    Console.WriteLine("  2) Sign & execute a transaction");
    Console.WriteLine("  q) Quit");
    Console.Write("> ");

    string input = Console.ReadLine()?.Trim() ?? "";

    if (input.Equals("q", StringComparison.OrdinalIgnoreCase))
    {
        Console.WriteLine("Goodbye!");
        break;
    }

    switch (input)
    {
        case "1":
            // Sign message
            Console.Write("Enter message to sign: ");
            string msg = Console.ReadLine() ?? "";

            try
            {
                var result = Web3.SignMessage("", msg);
                if (result.Cancelled)
                {
                    Console.WriteLine("[Cancelled] User declined to sign.");
                }
                else if (!string.IsNullOrEmpty(result.Error))
                {
                    Console.WriteLine($"[Error] {result.Error}");
                }
                else
                {
                    Console.WriteLine($"[Success] Signature: {result.Signature}");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[Exception] {ex.Message}");
            }
            break;

        case "2":
            // Sign & execute transaction
            Console.WriteLine("Building transaction and sending for signing...");
            // TODO: Replace with actual transaction building logic
            string txBytes = "xxx";

            try
            {
                var txResult = Web3.SignAndExecuteTransaction("", txBytes);
                if (txResult.Cancelled)
                {
                    Console.WriteLine("[Cancelled] User declined transaction.");
                }
                else if (!string.IsNullOrEmpty(txResult.Error))
                {
                    Console.WriteLine($"[Error] {txResult.Error}");
                }
                else
                {
                    Console.WriteLine($"[Success] Submitted at: {txResult.CompletedAt}, Result: {txResult.Result}");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"[Exception] {ex.Message}");
            }
            break;

        default:
            Console.WriteLine("Invalid option. Please choose 1, 2, or q.");
            break;
    }

    Console.WriteLine(); // Blank line before next loop
}