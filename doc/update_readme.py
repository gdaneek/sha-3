import re, glob, os

def parse_benchmark_table(markdown_text):
    lines = [line.strip() for line in markdown_text.split('\n') if line.strip()]
    headers = [h.strip() for h in lines[0].split('|')[1:-1]]
    results = []
    for line in lines[2:]:
        if not line.startswith('|'): continue
        values = [v.strip() for v in line.split('|')[1:-1]]
        row = dict(zip(headers, values))
        results.append(row)

    return results

def parse_relative(relative_str):
    try:
        value_part = relative_str.split('±')[0].strip()
        return float(value_part)
    except (ValueError, AttributeError):
        return 0.0

def sort_benchmarks_by_relative(benchmark_data):
    return sorted(benchmark_data, key=lambda x: parse_relative(x['Relative']))

def natural_sort_key(filename):
    match = re.search(r'sha-3-(\d+)\.md', filename.lower())
    if match:
        return int(match.group(1))

    match = re.search(r'benchmark_(\d+)\.md', filename.lower())
    if match:
        return int(match.group(1))

    return 0

winners = []
for i in range(20): winners.append(dict())

def read_benchmark_files():
    all_files = glob.glob('*.md')
    benchmark_files = [
        f for f in all_files
        if re.search(r'(sha-3-\d+|benchmark_\d+)\.md$', f.lower())
    ]

    benchmark_files.sort(key=natural_sort_key)

    combined_content = []
    for file in benchmark_files:
        with open(file, 'r', encoding='utf-8') as f:
            content = f.read().strip()
            benchmark_data = parse_benchmark_table(content)
            a = sort_benchmarks_by_relative(benchmark_data)
            for i in range(len(a)):
                command = a[i]["Command"].replace("_224", "").replace("_256", "").replace("_384", "").replace("_512", "")
                if command not in winners[i]:
                    winners[i][command.split(" ")[0]] = 1
                else:
                     winners[i][command] += 1
            combined_content.append(f"### {os.path.basename(file).split('.')[0]}\n\n{content}\n")

    return "\n".join(combined_content)


def process_winners(winners_list):
    used_commands = set()
    places = {
        1: {'emoji': '🥇', 'commands': []},
        2: {'emoji': '🥈', 'commands': []},
        3: {'emoji': '🥉', 'commands': []}
    }
    current_place = 1
    dict_index = 0

    while current_place <= 3 and dict_index < len(winners_list):
        current_dict = winners_list[dict_index]
        dict_index += 1

        filtered_dict = {k: v for k, v in current_dict.items()
                       if k not in used_commands}

        if not filtered_dict:
            continue

        max_value = max(filtered_dict.values())
        top_commands = [k for k, v in filtered_dict.items() if v == max_value]

        places[current_place]['commands'].extend(top_commands)
        used_commands.update(top_commands)
        current_place += 1

    md_output = [
        "| Top | Command |",
        "|-----|---------|"
    ]

    for place in [1, 2, 3]:
        if places[place]['commands']:
            emoji = places[place]['emoji']
            commands = '<br>'.join(sorted(places[place]['commands']))
            md_output.append(f"| {emoji} | {commands} |".replace("`", ""))

    return '\n'.join(md_output)

def update_readme(benchmark_content):
    try:
        with open('README.md', 'r', encoding='utf-8') as f:
            readme_content = f.read()
    except FileNotFoundError:
        print("No README found")
        return

    pattern = re.compile(
        r'(<!--\s*BENCHMARK_START\s*-->).*?(<!--\s*BENCHMARK_END\s*-->)',
        re.DOTALL
    )

    updated_content = pattern.sub(
        f'\\1\n\n{benchmark_content}\n\\2',
        readme_content
    )

    with open('README.md', 'w', encoding='utf-8') as f:
        f.write(updated_content)


if __name__ == '__main__':
    benchmark_content = read_benchmark_files()
    if benchmark_content:
        tt = f"### Summary\n\n"
        update_readme(benchmark_content + f"\n\n{tt}{process_winners(winners)}\n" )
        print("README.md updated")
    else:
        print("No benchmarks found")
