from flask import Flask, request, jsonify, render_template  # <-- added render_template
from flask_cors import CORS
import subprocess
import os

app = Flask(__name__)
CORS(app)

@app.route('/')
def home():
    return render_template('index.html')  # <-- serve the HTML UI

@app.route('/autocomplete', methods=['GET'])
def autocomplete():
    query = request.args.get('query', '').strip()

    if not query:
        return jsonify({'suggestions': [], 'error': 'Empty query'}), 400

    executable_path = os.path.join(os.getcwd(), 'autocomplete.exe')

    if not os.path.exists(executable_path):
        return jsonify({'suggestions': [], 'error': 'C++ autocomplete executable not found'}), 500

    try:
        result = subprocess.run([executable_path, query], capture_output=True, text=True, check=True)
        suggestions = [line.strip() for line in result.stdout.strip().split('\n') if line.strip()]
        return jsonify({'suggestions': suggestions})
    except subprocess.CalledProcessError as e:
        return jsonify({'suggestions': [], 'error': f'Execution error: {str(e)}'}), 500
    except Exception as e:
        return jsonify({'suggestions': [], 'error': f'Unexpected error: {str(e)}'}), 500

@app.route('/add_word', methods=['POST'])
def add_word():
    data = request.get_json()
    if not data or 'word' not in data:
        return jsonify({'error': 'No word provided'}), 400

    word = data['word'].strip()
    if not word:
        return jsonify({'error': 'Empty word'}), 400

    # Ensure no trailing whitespace and only one newline
    word_to_write = word.strip() + '\n'

    words_file = os.path.join(os.getcwd(), 'words.txt')
    import time
    try:
        with open(words_file, 'a', encoding='utf-8') as f:
            f.write(word_to_write)
            f.flush()
        time.sleep(0.1)  # small delay to ensure file write is flushed
        return jsonify({'message': f'Word "{word}" added successfully'})
    except Exception as e:
        return jsonify({'error': f'Failed to add word: {str(e)}'}), 500

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
