using Playtron.SDK;

Console.WriteLine("Running examples for SDK Manager");

// Virtual Keyboard
Console.WriteLine("Opening virtual keyboard...");
Manager.ShowKeyboard();

Console.WriteLine("Waiting 5 seconds...");
Thread.Sleep(5000);

Console.WriteLine("Hiding virtual keyboard...");
Manager.HideKeyboard();

/** ---- **/

Console.WriteLine("Waiting 2 seconds...");
Thread.Sleep(2000);

// Browser
const string URL = "https://google.com";
Console.WriteLine($"Opening browser URL:{URL}...");
Manager.OpenBrowser(URL);

Console.WriteLine("Waiting 5 seconds...");
Thread.Sleep(5000);

Console.WriteLine($"Closing browser...");
Manager.CloseBrowser();
