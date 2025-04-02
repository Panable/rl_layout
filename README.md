# Raylib JSON Layout Renderer

This project generates a graphical layout using Raylib from a JSON specification. It defines a grid-based structure and places UI components accordingly.

## Features
- Reads a JSON configuration to define a grid layout
- Uses Raylib to render components as colored rectangles
- Supports dynamic resizing
- Similar in concept to CSS Grid layout

## Installation and Build Instructions

### Prerequisites
- `gcc` (or another C compiler)
- `make`
- `raylib`

### Build Steps
```sh
make
```

### Run the Program
```sh
./build/layout
```

## JSON Specification
The layout is defined in a JSON file (e.g., `resources/test1.json`). Below is an example:

```json
{
  "specification": {
    "rows": 12,
    "cols": 12,
    "navbar_colour": "#181818",
    "tabs": [
      {
        "label": "System",
        "components": [
          {
            "name": "schematic information",
            "layout": {
              "row_start": 1,
              "row_end": 6,
              "col_start": 1,
              "col_end": 6
            }
          },
          {
            "name": "schematic diagram",
            "layout": {
              "row_start": 1,
              "row_end": 6,
              "col_start": 7,
              "col_end": 12
            }
          },
          {
            "name": "charts",
            "layout": {
              "row_start": 7,
              "row_end": 12,
              "col_start": 1,
              "col_end": 12
            }
          }
        ]
      }
    ]
  }
}
```

## Comparison to CSS Grid
This layout system is conceptually similar to CSS Grid:

| Feature       | JSON Layout (C)                 | CSS Grid Equivalent        |
|--------------|--------------------------------|----------------------------|
| Grid Definition | `rows`, `cols` in JSON | `grid-template-rows`, `grid-template-columns` |
| Component Positioning | `row_start`, `row_end`, `col_start`, `col_end` | `grid-row-start`, `grid-row-end`, `grid-column-start`, `grid-column-end` |
| Nested Layouts | JSON object hierarchy | CSS grid inside another grid |

### Example CSS Equivalent
```css
div.container {
    display: grid;
    grid-template-rows: repeat(12, 1fr);
    grid-template-columns: repeat(12, 1fr);
}

div.schematic-info {
    grid-row: 1 / 7; /* spans from line 1 to 6 (exclusive) */
    grid-column: 1 / 7;
}

div.schematic-diagram {
    grid-row: 1 / 7;
    grid-column: 7 / 13;
}

div.charts {
    grid-row: 7 / 13;
    grid-column: 1 / 13;
}
```

## Project Structure
```
.
├── build
│   ├── layout (executable)
│   └── resources
│       ├── test1.json
│       └── test.json
├── src
│   ├── json_helper.c
│   ├── json_helper.h
│   ├── layout.c
│   ├── resources
│   ├── vendor
│   │   ├── cJSON.c
│   │   ├── cJSON.h
│   │   └── raylib/
├── Makefile
└── README.md
```

## License
This project is licensed under the MIT License.
