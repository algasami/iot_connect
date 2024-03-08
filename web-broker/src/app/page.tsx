"use client";
import React, { useEffect } from "react";
import Link from "next/link";

function update_canvas(elem: HTMLCanvasElement, queue: number[]) {
  const ctx = elem.getContext("2d");
  if (ctx) {
    ctx.clearRect(0, 0, elem.width, elem.height);
    // bar chart
    const bar_width = elem.width / queue.length;
    for (let i = 0; i < queue.length; i++) {
      const bar_height = (queue[i] / 1024) * elem.height;
      ctx.fillStyle = `rgb(0, 100, ${Math.floor(
        255 - (queue[i] / 1024) * 255
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
  const ref = React.useRef<HTMLCanvasElement>(null);
  useEffect(() => {
    let moisture_queue: number[] = [];
    setInterval(() => {
      fetch("/api", {
        method: "GET",
      })
        .then((response) => response.json())
        .then((data) => {
          const val = data.moisture as number;
          moisture_queue.push(val);
          if (moisture_queue.length > 10) {
            moisture_queue.shift();
          }
          update_canvas(ref.current as HTMLCanvasElement, moisture_queue);
        });
    }, 300);
  });
  return (
    <main className="flex min-h-screen flex-col items-center justify-between p-24 bg-slate-900">
      <h1>Web Broker</h1>
      <canvas width={500} height={300} ref={ref} />
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
