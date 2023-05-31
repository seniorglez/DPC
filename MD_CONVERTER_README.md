# DPC - Markdown to HTML Converter

[![License: GPL-3.0](https://img.shields.io/badge/License-GPL--3.0-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Welcome to the Markdown to HTML Converter! This command-line tool converts Markdown files into HTML files. It parses the Markdown syntax and generates corresponding HTML tags for headers, paragraphs, and tables.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Installation

To compile and use the Markdown to HTML Converter, jsut use gcc:

   ```shell
   gcc main.c -o converter
   ```

## Usage

Once you have compiled the code, you can use the Markdown to HTML Converter as follows:

1. Prepare your Markdown file: Create a Markdown file (e.g., `input.md`) that you want to convert to HTML. Place it in the same directory as the `converter` executable.

2. Run the converter:

   ```shell
   ./converter
   ```

The converter will read the `input.md` file and generate an HTML file named `output.html`. Open `output.html` in a web browser to see the converted content.

Note: The converter applies a simple CSS style to the generated HTML tables. You can customize the CSS by modifying the `style` variable in the code.

## Contributing

Contributions are welcome! If you find any issues or want to enhance the converter, feel free to open a pull request.

## License

This project is licensed under the GNU General Public License v3.0. For more details, see the [LICENSE](LICENSE) file.

---

© 2023 Diego Domínguez Gonz

