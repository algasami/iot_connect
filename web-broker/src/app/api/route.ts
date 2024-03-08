let current_moisture = 1024;

function abs(x: number) {
  return x < 0 ? -x : x;
}

export async function POST(request: Request) {
  let new_moisture = (await request.json()).moisture;

  if (abs(new_moisture - current_moisture) > 30) {
    current_moisture = new_moisture;
    fetch(process.env.DISCORD_HOOK!, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        username: "Moisture Alert - Firmware EASY",
        content: `Moisture level is ${current_moisture}`,
      }),
    });
  }

  return Response.json({
    success: true,
  });
}

export async function GET() {
  return Response.json({
    moisture: current_moisture,
  });
}
