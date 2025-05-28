using System.Net.Http.Headers;
using Playtron.SDK.PACT;

Console.WriteLine("Checking if on a Playtron device...");
if (Playtron.SDK.OS.IsPlaytron())
{
    Console.WriteLine("Running on Playtron!");
}
else
{
    Console.WriteLine("Not running on Playtron!");
    return;
}

Console.WriteLine("Creating attestation client...");
var attestationClient = new AttestationClient();

Console.WriteLine("Creating attestation session...");
var sessionInfo = await attestationClient.CreateSession();
Console.WriteLine($"Session ID: {sessionInfo.SessionId}");
Console.WriteLine($"Nonce: {System.Text.Encoding.ASCII.GetString(sessionInfo.Nonce)}");

Console.WriteLine("Getting quote from TPM...");
var quote = attestationClient.GetQuote(sessionInfo.Nonce);
Console.WriteLine($"Quote: {quote}");

Console.WriteLine("Sending attestation request...");
HttpClient client = new()
{
    BaseAddress = new Uri(Environment.GetEnvironmentVariable("PACT_ATTESTATION_URL")!)
};
client.DefaultRequestHeaders.Add("Accept", "application/json");

var requestContent = new StringContent(quote, MediaTypeHeaderValue.Parse("application/json"));
requestContent.Headers.Add("X-Session-Id", sessionInfo.SessionId);

var response = await client.PostAsync("api/v1/session/attest", requestContent);
if (!response.IsSuccessStatusCode)
{
    Console.WriteLine($"Attestation request failed with status code: {response.StatusCode.ToString()}");
    return;
}

string token = await response.Content.ReadAsStringAsync();

Console.WriteLine($"Attestation Token: {token}");