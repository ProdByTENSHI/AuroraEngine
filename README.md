# 🎮 2D C++ Game Engine (SDL2 Powered)

A lightweight, high-performance **2D Game Engine** built in **C++** using **SDL2**, designed with **multithreading** at its core to deliver smooth gameplay while keeping debugging tools and editor systems responsive.

---

## 🚀 Overview

This project is a custom-built 2D game engine focused on:

- ⚡ High performance
- 🧵 Multithreaded architecture
- 🛠️ Responsive debugging & tooling
- 🎯 Clean and modular C++ design
- 🎮 SDL2-powered rendering & input

Unlike traditional single-threaded engines where debugging tools can impact runtime performance, this engine separates responsibilities across threads to ensure that **game logic remains smooth and uninterrupted**.

---

## 🧠 Architecture Philosophy

The engine is designed around a **separation of concerns**, distributing workloads across multiple threads:

- 🎮 **Game Thread** – Handles gameplay logic and updates  
- 🖼️ **Render Thread** – Manages SDL2 rendering pipeline  
- 🛠️ **Debug/Tooling Thread(s)** – Keeps debugging UI and performance tools responsi
