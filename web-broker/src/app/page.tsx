"use client"; // 在客戶端執行
import React, { useEffect } from "react";
import Link from "next/link";

function update_canvas(elem: HTMLCanvasElement, queue: number[]) {
  const ctx = elem.getContext("2d");
  // canvas 畫圖，長條圖
  if (ctx) {
    ctx.clearRect(0, 0, elem.width, elem.height);
    // bar chart
    const bar_width = elem.width / queue.length;
    for (let i = 0; i < queue.length; i++) {
      const bar_height = (queue[i] / 1024) * elem.height;
      ctx.fillStyle = `rgb(0, 100, ${Math.floor(
        255 - (queue[i] / 1024) * 255
        // 顏色深淺：濕度越高，顏色越淺
      )})`;
      ctx.fillRect(
        i * bar_width,
        elem.height - bar_height,
        bar_width - 10,
        bar_height
      );
      // write value center of bar zindex

      ctx.fillStyle = "white";
      ctx.font = "12px Arial";
      ctx.textAlign = "center";
      ctx.fillText(
        queue[i].toString(),
        i * bar_width + bar_width / 2,
        elem.height - bar_height + 20
      );
    }
  }
}
export default function Home() {
  const ref = React.useRef<HTMLCanvasElement>(null); // react參考
  // 可以想成是一個物件的指標

  useEffect(() => {
    // 用useEffect，讓程式在準備好後執行
    let moisture_queue: number[] = [];
    setInterval(() => {
      fetch("/api", {
        method: "GET", // 取得濕度資料
      })
        .then((response) => response.json())
        .then((data) => {
          const val = data.moisture as number;
          // 實作有限長度的佇列
          moisture_queue.push(val);
          if (moisture_queue.length > 10) {
            moisture_queue.shift(); // 砍頭，保持長度為10
          }
          update_canvas(ref.current as HTMLCanvasElement, moisture_queue);
        });
    }, 300); // 300ms更新一次
  });
  return (
    <main className="flex min-h-screen flex-col items-center justify-between p-24 bg-slate-900">
      <h1>Web Broker</h1>
      <canvas width={500} height={300} ref={ref} />
      {/**
       * 我們的canvas是一個500x300的矩形，我們將它放在一個flexbox中，這樣它就會自動居中。
       */}
      <div>
        For more information, visit{" "}
        <Link
          href="https://algasami.github.io/posts/20240305-esp"
          className="text-blue-500 hover:text-blue-300"
        >
          algasami.github.io
        </Link>
      </div>
      <footer>Smelling Moisture since 2024</footer>
    </main>
  );
}
