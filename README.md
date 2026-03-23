# Autocomplete Search Engine


A full-stack autocomplete search engine built for efficient and user-friendly word suggestions, leveraging a C++ Trie for fast prefix matching and a modern web interface. Developed as a Data Structures and Algorithms (DSA) project to demonstrate proficiency in C++, Flask, and front-end development, deployed on Render for global access.

## Features
- **Multi-Word Query Support**: Autocomplete suggestions for the last word in a query (e.g., "apple b" suggests "banana", "band").
- **Keyboard Navigation**: Navigate suggestions using **ArrowDown**/**ArrowUp** and select with **Enter**.
- **Prefix Highlighting**: Bold matching prefixes in suggestions (e.g., "**app**le" for "app").
- **Clear Input**: Reset input with a single click using the "✕" button.
- **Debounced API Calls**: 300ms debounce to optimize backend requests.
- **Loading Indicator**: Visual feedback during API calls for better UX.
- **Responsive Design**: Mobile-friendly interface with Tailwind CSS.
- **Efficient Backend**: C++ Trie-based autocomplete for O(m + k) performance, where m is the query length and k is the number of suggestions.

## Tech Stack
- **Front-End**: HTML, Tailwind CSS, JavaScript (fetch, DOM manipulation)
- **Back-End**: Flask (Python), C++ (Trie data structure)
- **Deployment**: Render (Static Site for front-end, Web Service for backend)
- **Tools**: Git, GitHub, g++ (C++ compilation), Python 3.8

## Project Structure
```
autocomplete-project/
├── .gitattributes        # Ensures LF line endings for Linux compatibility
├── .gitignore            # Ignores compiled binaries, Python cache, etc.
├── index.html            # Front-end with autocomplete UI
├── server.py             # Flask server for API
├── autocomplete.cpp      # C++ Trie for suggestion generation
├── words.txt             # Curated word list (~5,000–10,000 words)
├── requirements.txt      # Python dependencies (Flask, flask-cors)
└── README.md             # Project documentation
```

## Setup Instructions
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/[your-username]/autocomplete-project.git
   cd autocomplete-project
   ```

2. **Install Dependencies**:
   - Ensure Python 3.8+ and g++ are installed.
   - Install Python dependencies:
     ```bash
     pip install -r requirements.txt
     ```

3. **Compile C++ Backend**:
   ```bash
   g++ -o autocomplete autocomplete.cpp
   ```

4. **Run Flask Server**:
   ```bash
   python server.py
   ```

5. **Serve Front-End**:
   ```bash
   python -m http.server 8000
   ```
   - Access at `http://localhost:8000`.

## Usage
1. Open `http://localhost:8000`..
2. Type a query (e.g., "app" or "apple b").
3. View suggestions with bolded prefixes (e.g., "**app**le").
4. Navigate with **ArrowDown**/**ArrowUp**, select with **Enter**, or click a suggestion.
5. Click the "✕" button to clear the input.
6. Observe the loading indicator during API calls.



