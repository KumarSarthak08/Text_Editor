# Text Editor with Undo and Redo (C Language)

This project is a simple command-line **text editor** written in **C** that supports basic **text insertion**, **undo**, and **redo** functionalities using **linked lists** and **stacks**.

## Features

- Insert characters to the text
- Undo the last insertion or deletion
- Redo the last undone operation
- View current text state
- Exit the editor gracefully

## How It Works

- The text is stored as a **singly linked list**, where each node represents a character.
- Two stacks (`undoStack` and `redoStack`) are used to track user actions:
  - Insertions (`'i'`) and deletions (`'d'`) are pushed to the **undo stack**.
  - When undoing an operation, it is moved to the **redo stack**, and vice versa.

## Commands

| Command        | Description                          |
|----------------|--------------------------------------|
| `/undo`        | Undo the last operation              |
| `/redo`        | Redo the last undone operation       |
| `/quit`        | Exit the editor                      |
| any text input | Appends the text to the current text |

## Usage

### Compile the program

```bash
gcc editor.c -o editor
