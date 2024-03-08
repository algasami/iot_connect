import type { Metadata } from "next";
import { Inter } from "next/font/google";
import "./globals.css";

// layout.tsx, page.tsx這些都是next 14的新功能。
// 可以想成是一連串的endofunction (f: A -> A)

const inter = Inter({ subsets: ["latin"] });

export const metadata: Metadata = {
  title: "Web Broker",
  description: "Smelling Moisture",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <body className={inter.className}>{children}</body>
    </html>
  );
}
