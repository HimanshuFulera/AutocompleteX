import os

BASE_DIR = os.path.dirname(os.path.abspath(__file__))

@app.route('/autocomplete', methods=['GET'])
def autocomplete():
    query = request.args.get('query', '').strip()

    if not query:
        return jsonify({'suggestions': [], 'error': 'Empty query'}), 400

    executable_path = os.path.join(BASE_DIR, 'autocomplete')

    if not os.path.exists(executable_path):
        return jsonify({'suggestions': [], 'error': 'C++ executable not found'}), 500

    try:
        result = subprocess.run([executable_path, query], capture_output=True, text=True, check=True)
        suggestions = [line.strip() for line in result.stdout.strip().split('\n') if line.strip()]
        return jsonify({'suggestions': suggestions})
    except Exception as e:
        return jsonify({'suggestions': [], 'error': str(e)}), 500


@app.route('/add_word', methods=['POST'])
def add_word():
    data = request.get_json()
    word = data.get('word', '').strip()

    words_file = os.path.join(BASE_DIR, 'words.txt')

    with open(words_file, 'a', encoding='utf-8') as f:
        f.write(word + '\n')

    return jsonify({'message': f'Word "{word}" added successfully'})


if __name__ == '__main__':
    port = int(os.environ.get("PORT", 10000))
    app.run(host='0.0.0.0', port=port)
