# 🎮 2D C++ Game Engine (SDL2 Powered)

A lightweight, high-performance **2D Game Engine** built in **C++** using **SDL2**, designed with **multithreading** at its core to deliver smooth gameplay while keeping debugging tools and editor systems responsive.

---

## 🚀 Overview

This project is a custom-built 2D game engine focused on:

- ⚡ High performance
- 🛠️ Responsive debugging & tooling
- 🎯 Clean and modular C++ design
- 🎮 SDL2-powered rendering & input

The Project Trello Board can be found here: https://trello.com/b/xrdjiR9K/aurora-engine

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

## 🎮 Input System

The Input System is double buffered which means that there is no access Lock Up.
Instead of an Event Driven System we use a State Driven approach to handle Input.
This allows us to check for Key Combinations, Key States etc without ugly Lambda
Functions.

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