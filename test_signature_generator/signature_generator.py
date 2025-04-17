import os
import random
import argparse

# ---------------------------------------------
# Configuration lists for signature generation
# ---------------------------------------------
prefixes = [
    'Trojan', 'Worm', 'Virus', 'Rootkit', 'Spyware', 'Adware', 'Ransom', 'Backdoor'
]
suffixes = [
    'Alpha', 'Beta', 'Gamma', 'Delta', 'Epsilon', 'Zeta', 'Omega', 'Sigma', 'Nebula', 'Quantum'
]
description_templates = [
    'A {name} that attempts to steal user credentials.',
    'A {name} which encrypts files and demands ransom.',
    'A {name} that propagates via email attachments.',
    'A {name} targeting system processes for privilege escalation.',
    'A {name} designed to exfiltrate sensitive data silently.',
    'A {name} that modifies system configurations to allow remote access.'
]


# ---------------------------------------------
# Generate virus signature file
# ---------------------------------------------
def generate_signatures(output_file: str, count: int = 100):
    signatures = []
    with open(output_file, 'w') as f:
        for i in range(count):
            length = random.randint(8, 20)  # length in bytes
            pattern = ''.join(f"{random.randint(0, 255):02X}" for _ in range(length))
            prefix = random.choice(prefixes)
            suffix = random.choice(suffixes)
            name = f"{prefix}.{suffix}{i:03d}"
            desc = random.choice(description_templates).format(name=name)
            f.write(f"{pattern};{name};{desc}\n")
            signatures.append({'pattern': pattern, 'name': name})
    return signatures


# ---------------------------------------------
# Generate nested folder structure and files
# ---------------------------------------------
def generate_files(
        base_dir: str,
        max_depth: int,
        max_dirs_per_level: int,
        max_files_per_dir: int,
        max_file_size: int,
        signatures: list,
        embed_count: int,
        tree_file: str
):
    os.makedirs(base_dir, exist_ok=True)
    file_paths = []
    infected_map = {}

    def recurse(current_dir: str, depth: int):
        # generate files
        num_files = random.randint(1, max_files_per_dir)
        for _ in range(num_files):
            fname = f"file_{random.randint(0, 1_000_000_000)}.bin"
            path = os.path.join(current_dir, fname)
            size = random.randint(0, max_file_size)
            with open(path, 'wb') as fout:
                fout.write(os.urandom(size))
            file_paths.append(path)

        # generate subdirectories
        if depth < max_depth:
            num_dirs = random.randint(0, max_dirs_per_level)
            for _ in range(num_dirs):
                dname = f"dir_{random.randint(0, 1_000_000_000)}"
                subdir = os.path.join(current_dir, dname)
                os.makedirs(subdir, exist_ok=True)
                recurse(subdir, depth + 1)

    recurse(base_dir, 0)

    embed_paths = random.sample(file_paths, min(embed_count, len(file_paths)))
    for path in embed_paths:
        sig = random.choice(signatures)
        pattern = sig['pattern']
        with open(path, 'r+b') as fout:
            data = fout.read()
            pos = random.randint(0, len(data))
            fout.seek(pos)
            fout.write(bytes.fromhex(pattern))
        infected_map[path] = sig['name']

    with open(tree_file, 'w') as tree_f:
        def write_tree(directory, level=0):
            tree_f.write(f"{'  ' * level}{os.path.basename(directory)}/\n")
            entries = sorted(os.listdir(directory))
            for entry in entries:
                full_path = os.path.join(directory, entry)
                if os.path.isdir(full_path):
                    write_tree(full_path, level + 1)
                else:
                    inf_mark = f" [INFECTED: {infected_map[full_path]}]" if full_path in infected_map else ""
                    tree_f.write(f"{'  ' * (level + 1)}{entry}{inf_mark}\n")

        write_tree(base_dir)

        tree_f.write(f"\nTotal files: {len(file_paths)}\n")
        tree_f.write(f"Infected files: {len(infected_map)}\n")

    return infected_map, file_paths


# ---------------------------------------------
# Main CLI
# ---------------------------------------------
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate virus signatures and test files.')
    parser.add_argument('--sig-file', default='signatures.txt', help='Output file for signatures')
    parser.add_argument('--sig-count', type=int, default=100, help='Number of signatures to generate')
    parser.add_argument('--output-dir', default='test_dir', help='Base directory for test files')
    parser.add_argument('--max-depth', type=int, default=3, help='Maximum subdirectory depth')
    parser.add_argument('--max-dirs', type=int, default=3, help='Max subdirs per level')
    parser.add_argument('--max-files', type=int, default=5, help='Max files per directory')
    parser.add_argument('--max-size', type=int, default=5 * 1024 * 1024, help='Max file size in bytes')
    parser.add_argument('--embed-count', type=int, default=10, help='Number of files to embed signatures into')
    parser.add_argument('--tree-file', default='file_tree.txt', help='File to save the directory structure')
    args = parser.parse_args()

    sigs = generate_signatures(args.sig_file, args.sig_count)
    print(f"Generated {len(sigs)} signatures into {args.sig_file}")

    infected_map, files = generate_files(
        args.output_dir,
        args.max_depth,
        args.max_dirs,
        args.max_files,
        args.max_size,
        sigs,
        args.embed_count,
        args.tree_file
    )
    print(f"Generated {len(files)} files under {args.output_dir}, embedded in {len(infected_map)} files.")
    print(f"Directory structure saved to {args.tree_file}")
# python signature_generator.py --sig-file signatures.txt --sig-count 500 --output-dir my_test_dir --max-depth 6 --max-files 500 --max-size 100000 --embed-count 500 --tree-file inf_file_tree.txt
