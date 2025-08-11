# Ziggy - JSON Path Checker

A simple JSON path checker built with C and compiled using Zig. This tool reads JSON files and checks whether specified paths exist within the JSON structure.

## Features

- Parse JSON files using the cJSON library
- Check for path existence using dot notation (e.g., `user.profile.name`)
- Returns boolean output (`true`/`false`)
- Built with Zig's build system for easy compilation

## Prerequisites

- Zig compiler
- The cJSON library (included in `src/`)

## Building

```bash
zig build
```

This will create the executable at `bin/json-parser`.

## Usage

```bash
./bin/json-parser <json_file> <path>
```

### Examples

Given a JSON file `test.json`:
```json
{
  "user": {
    "name": "John Doe",
    "profile": {
      "age": 30,
      "preferences": {
        "theme": "dark"
      }
    }
  },
  "settings": {
    "version": "1.0.0"
  }
}
```

Check if paths exist:
```bash
./bin/json-parser test.json user.name                    # Returns: true
./bin/json-parser test.json user.profile.preferences.theme # Returns: true
./bin/json-parser test.json user.nonexistent             # Returns: false
./bin/json-parser test.json settings.version             # Returns: true
```

## Path Notation

Use dot notation to specify nested paths:
- `user` - top level key
- `user.name` - nested key
- `user.profile.preferences.theme` - deeply nested key

## Project Structure

```
ziggy/
├── src/
│   ├── json_parser.c    # Main application code
│   ├── cJSON.c          # cJSON library source
│   └── cJSON.h          # cJSON library header
├── bin/                 # Compiled binaries
├── test.json           # Sample JSON file
├── build.zig           # Zig build configuration
└── README.md           # This file
```

## Development

To run the program directly:
```bash
zig build run -- test.json user.name
```

The program will:
1. Read the specified JSON file
2. Parse it using cJSON
3. Navigate to the specified path
4. Output `true` if the path exists, `false` otherwise