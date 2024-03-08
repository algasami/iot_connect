let current_moisture = 1024;

function abs(x: number) {
  return x < 0 ? -x : x;
}

// 定義非同步函式
export async function POST(request: Request) {
  let new_moisture = (await request.json()).moisture;

  if (abs(new_moisture - current_moisture) > 30) {
    current_moisture = new_moisture;
    // 平行處理discord hook，避免等待時間過長，造成回應時間過長
    fetch(process.env.DISCORD_HOOK!, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      // JSON.stringify() 將js物件轉換成字串
      body: JSON.stringify({
        username: "Moisture Alert - Firmware EASY",
        content: `Moisture level is ${current_moisture}`, // ${}替代成你的訊息
      }),
    });
  }

  return Response.json({
    success: true,
  });
}

// 供給前端取得濕度資料
export async function GET() {
  return Response.json({
    moisture: current_moisture,
  });
}
