### WebCrawler_C
This is a simple web crawler written in C using `libcurl` to fetch HTML content and `libxml2` to parse it.

#### Features
- Fetch HTML content from a specified URL.
- Parse the HTML to extract specific elements (e.g., the title).

#### Prerequisites
- `libcurl`
- `libxml2`

#### Installation
1. Install the required libraries:
   ```sh
   sudo apt-get install libcurl4-gnutls-dev libxml2-dev
   ```
2. Clone the repository:
   ```sh
   git clone https://github.com/Wasay-Rana/WebCrawler_C.git
   cd WebCrawler_C
   ```

#### Usage
1. Compile the code using `gcc`:
   ```sh
   gcc -o webcrawler crawl.c -lcurl -lxml2
   ```
2. Run the executable:
   ```sh
   ./webcrawler
   ```

#### Example
The program will fetch HTML content from `https://muhammad-wasay.vercel.app`, parse it, and print the title to the console. The fetched HTML will also be saved to `output.html`.

#### License
Feel free to customize any part of this README to better suit your project!
