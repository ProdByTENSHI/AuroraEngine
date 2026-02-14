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

The Project Trello Board can be found here: https://trello.com/b/xrdjiR9K/aurora-engine

---

## 🧠 Architecture Philosophy

The engine is designed around a **separation of concerns**, distributing workloads across multiple threads:

- 🎮 **Game Thread** – Handles gameplay logic and updates  
- 🖼️ **Render Thread** – Manages SDL2 rendering pipeline  
- 🛠️ **Debug/Tooling Thread(s)** – Keeps debugging UI and performance tools responsi

---

## 🧩 Entity Component System (ECS)

The engine includes a fully integrated **Entity Component System (ECS)** architecture.

The ECS provides:

- 🧱 Data-oriented design for improved performance
- ⚡ Efficient component iteration
- 🔄 Flexible entity composition
- 🧠 Clear separation between data (components) and behavior (systems)

This allows complex game objects to be built from simple, reusable components while maintaining high performance and scalability.

---

## 🗺️ Tile Editor

The engine also includes a built-in **Tile Editor** to streamline 2D level creation.

Features include:

- 🧩 Tile-based level design
- 🖱️ Interactive editing tools
- 💾 Save/load tile maps
- 🧱 Layer support
- 🎮 Direct integration with the engine runtime

The tile editor is designed to work seamlessly with the engine's ECS and rendering pipeline, making rapid level prototyping fast and efficient.

---